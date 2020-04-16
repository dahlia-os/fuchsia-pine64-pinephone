// File is automatically generated; do not modify.
// See tools/fidl/measure-tape/README.md

#ifndef LIB_UI_SCENIC_CPP_COMMANDS_SIZING_H_
#define LIB_UI_SCENIC_CPP_COMMANDS_SIZING_H_

#include <fuchsia/ui/scenic/cpp/fidl.h>


namespace measure_tape {
namespace fuchsia {
namespace ui {
namespace scenic {

struct Size {
  explicit Size(int64_t num_bytes, int64_t num_handles)
    : num_bytes(num_bytes), num_handles(num_handles) {}

  const int64_t num_bytes;
  const int64_t num_handles;
};

// Helper function to measure ::fuchsia::ui::scenic::Command.
//
// In most cases, the size returned is a precise size. Otherwise, the size
// returned is a safe upper-bound.
Size Measure(const ::fuchsia::ui::scenic::Command& value);


}  // scenic
}  // ui
}  // fuchsia
}  // measure_tape

#endif  // LIB_UI_SCENIC_CPP_COMMANDS_SIZING_H_
