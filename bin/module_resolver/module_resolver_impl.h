// Copyright 2017 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PERIDOT_BIN_MODULE_RESOLVER_MODULE_RESOLVER_IMPL_H_
#define PERIDOT_BIN_MODULE_RESOLVER_MODULE_RESOLVER_IMPL_H_

#include <functional>

#include "lib/module_resolver/fidl/module_resolver.fidl.h"

#include "garnet/public/lib/fidl/cpp/bindings/binding_set.h"
#include "peridot/lib/module_manifest_repository/module_manifest_repository.h"

namespace maxwell {

class ModuleResolverImpl : modular::ModuleResolver {
 public:
  ModuleResolverImpl(std::string manifest_repository_path);
  ~ModuleResolverImpl() override;

  void Connect(fidl::InterfaceRequest<modular::ModuleResolver> request);

  // |ModuleResolver|
  // This is public because we call it in our unittest.
  void FindModules(modular::DaisyPtr daisy,
                   modular::ResolverScoringInfoPtr scoring_info,
                   const FindModulesCallback& done) override;

 private:
  void OnNewManifestEntry(
      modular::ModuleManifestRepository::Entry entry);

  // TODO(thatguy): At some point, factor the index functions out of
  // ModuleResolverImpl so that they can be re-used by the general all-modules
  // Ask handler.
  std::unique_ptr<modular::ModuleManifestRepository> manifest_repository_;
  uint32_t next_entry_id_;
  std::map<uint32_t, modular::ModuleManifestRepository::Entry> entries_;

  std::map<std::string, std::set<uint32_t>> verb_to_entry_;

  fidl::BindingSet<modular::ModuleResolver> bindings_;

  FXL_DISALLOW_COPY_AND_ASSIGN(ModuleResolverImpl);
};

}  // namespace maxwell

#endif  // PERIDOT_BIN_MODULE_RESOLVER_MODULE_RESOLVER_IMPL_H_
