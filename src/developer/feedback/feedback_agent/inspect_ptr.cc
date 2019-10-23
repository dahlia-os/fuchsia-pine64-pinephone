// Copyright 2019 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "src/developer/feedback/feedback_agent/inspect_ptr.h"

#include <lib/async/cpp/task.h>
#include <lib/async/default.h>
#include <lib/fit/bridge.h>
#include <lib/fit/promise.h>
#include <zircon/errors.h>
#include <zircon/status.h>
#include <zircon/types.h>

#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "src/lib/fsl/vmo/strings.h"
#include "src/lib/inspect_deprecated/query/discover.h"
#include "src/lib/inspect_deprecated/query/json_formatter.h"
#include "src/lib/inspect_deprecated/query/location.h"
#include "src/lib/inspect_deprecated/query/read.h"
#include "src/lib/inspect_deprecated/query/source.h"
#include "src/lib/syslog/cpp/logger.h"

namespace feedback {
namespace {

template <typename T>
struct LockedBridge {
  fit::bridge<T, void> bridge;
  std::mutex lock;
};

}  // namespace

fit::promise<fuchsia::mem::Buffer> CollectInspectData(async_dispatcher_t* dispatcher,
                                                      zx::duration timeout) {
  using Locations = std::vector<inspect_deprecated::Location>;
  // First, we discover all the Inspect entrypoints under the realm of the calling component.

  // We use a fit::bridge to create a fit::promise that will be completed when the discovery is
  // done, returning the discovered locations.
  //
  // We use a shared_ptr to share the bridge between this function, the async loop on which we post
  // the delayed task to timeout and the second thread on which we run the discovery.
  std::shared_ptr<LockedBridge<Locations>> discovery_done =
      std::make_shared<LockedBridge<Locations>>();

  // fit::promise does not have the notion of a timeout. So we post a delayed task that will call
  // the completer after the timeout and return an error.
  if (const zx_status_t status = async::PostDelayedTask(
                                     dispatcher,
                                     [discovery_done] {
                                       {  // We keep the lock_guard's scope to a minimum.
                                         std::lock_guard<std::mutex> lock(discovery_done->lock);
                                         if (!discovery_done->bridge.completer) {
                                           return;
                                         }
                                         discovery_done->bridge.completer.complete_error();
                                       }

                                       FX_LOGS(ERROR) << "Inspect data discovery timed out";
                                     },
                                     timeout) != ZX_OK) {
    FX_PLOGS(ERROR, status) << "Failed to post delayed task";
    FX_LOGS(ERROR)
        << "Skipping Inspect data collection as Inspect discovery is not safe without a timeout";
    return fit::make_result_promise<fuchsia::mem::Buffer>(fit::error());
  }

  // We run the discovery in a separate thread as the calling component will itself be discovered
  // and we don't want to deadlock it, cf. CF-756.
  //
  // Note that this thread could be left dangling if it hangs forever trying to opendir() a
  // currently serving out/ directory from one of the discovered components. It is okay to have
  // potentially dangling threads as we run each fuchsia.feedback.DataProvider request in a separate
  // process that exits when the connection with the client is closed.
  std::thread([discovery_done]() mutable {
    Locations locations = inspect_deprecated::SyncFindPaths("/hub");

    std::lock_guard<std::mutex> lock(discovery_done->lock);
    if (!discovery_done->bridge.completer) {
      return;
    }

    if (locations.empty()) {
      FX_LOGS(ERROR) << "Failed to find any Inspect location";
      discovery_done->bridge.completer.complete_error();
    } else {
      discovery_done->bridge.completer.complete_ok(std::move(locations));
    }
  }).detach();

  // Then, we connect to each entrypoint and read asynchronously its Inspect data.
  return discovery_done->bridge.consumer.promise_or(fit::error())
      .and_then([](Locations& locations) {
        std::vector<fit::promise<inspect_deprecated::Source, std::string>> sources;
        for (auto location : locations) {
          if (location.directory_path.find("system_objects") == std::string::npos) {
            sources.push_back(inspect_deprecated::ReadLocation(std::move(location)));
          }
        }

        return fit::join_promise_vector(std::move(sources))
            .and_then([](std::vector<fit::result<inspect_deprecated::Source, std::string>>& sources)
                          -> fit::result<fuchsia::mem::Buffer> {
              std::vector<inspect_deprecated::Source> ok_sources;
              for (auto& source : sources) {
                if (source.is_ok()) {
                  inspect_deprecated::Source ok_source = source.take_value();
                  ok_source.SortHierarchy();
                  ok_sources.push_back(std::move(ok_source));
                } else {
                  FX_LOGS(ERROR) << "Failed to read one Inspect source: " << source.take_error();
                }
              }

              if (ok_sources.empty()) {
                FX_LOGS(WARNING) << "No valid Inspect sources found";
                return fit::error();
              }

              fsl::SizedVmo vmo;
              if (!fsl::VmoFromString(inspect_deprecated::JsonFormatter(
                                          inspect_deprecated::JsonFormatter::Options{},
                                          inspect_deprecated::Formatter::PathFormat::ABSOLUTE)
                                          .FormatSourcesRecursive(ok_sources),
                                      &vmo)) {
                FX_LOGS(ERROR) << "Failed to convert Inspect data JSON string to vmo";
                return fit::error();
              }
              return fit::ok(std::move(vmo).ToTransport());
            })
            .or_else([]() {
              FX_LOGS(ERROR) << "Failed to get Inspect data";
              return fit::error();
            });
      });
}

}  // namespace feedback
