// Copyright 2020 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <lib/zx/bti.h>
#include <lib/zx/iommu.h>
#include <lib/zx/msi.h>
#include <lib/zx/resource.h>
#include <lib/zx/thread.h>
#include <zircon/syscalls/iommu.h>

#include <zxtest/zxtest.h>

namespace {

extern "C" zx_handle_t get_root_resource(void);

class RootResourceFixture : public zxtest::Test {
 public:
  void SetUp() override {
    zx_iommu_desc_dummy_t desc = {};
    root_resource_ = zx::unowned_resource(get_root_resource());
    ASSERT_OK(
        zx::iommu::create(*root_resource_, ZX_IOMMU_TYPE_DUMMY, &desc, sizeof(desc), &iommu_));
    ASSERT_OK(zx::bti::create(iommu_, 0, 0xdeadbeef, &bti_));
  }

  bool MsiTestsSupported() {
    zx::msi msi;
    return !(zx::msi::allocate(*root_resource_, 1, &msi) == ZX_ERR_NOT_SUPPORTED);
  }

 protected:
  zx::unowned_resource root_resource_;
  zx::iommu iommu_;
  zx::bti bti_;
};

bool WaitThread(const zx::thread& thread, uint32_t reason) {
  while (true) {
    zx_info_thread_t info;
    EXPECT_OK(thread.get_info(ZX_INFO_THREAD, &info, sizeof(info), nullptr, nullptr));
    if (info.state == reason) {
      return true;
    }
    zx::nanosleep(zx::deadline_after(zx::msec(1)));
  }
  return true;
}

// This is not really a function, but an entry point for a thread that has
// a tiny stack and no other setup. It's not really entered with the C ABI
// as such.  Rather, it's entered with the first argument register set to
// zx_handle_t and with the SP at the very top of the allocated stack.
// It's defined in pure assembly so that there are no issues with
// compiler-generated code's assumptions about the proper ABI setup,
// instrumentation, etc.
extern "C" void ThreadEntry(uintptr_t arg1, uintptr_t arg2);
// while (zx_interrupt_wait(static_cast<zx_handle_t>(arg1), nullptr) == ZX_OK);
// __builtin_trap();
__asm__(
    ".pushsection .text.ThreadEntry,\"ax\",%progbits\n"
    ".balign 4\n"
    ".type ThreadEntry,%function\n"
    "ThreadEntry:\n"
#ifdef __aarch64__
    "  mov w20, w0\n"  // Save handle in callee-saves register.
    "0:\n"
    "  mov w0, w20\n"           // Load saved handle into argument register.
    "  mov x1, xzr\n"           // Load nullptr into argument register.
    "  bl zx_interrupt_wait\n"  // Call.
    "  cbz w0, 0b\n"            // Loop if returned ZX_OK.
    "  brk #0\n"                // Else crash.
#elif defined(__x86_64__)
    "  mov %edi, %ebx\n"  // Save handle in callee-saves register.
    "0:\n"
    "  mov %ebx, %edi\n"          // Load saved handle into argument register.
    "  xor %edx, %edx\n"          // Load nullptr into argument register.
    "  call zx_interrupt_wait\n"  // Call.
    "  testl %eax, %eax\n"        // If returned ZX_OK...
    "  jz 0b\n"                   // ...loop.
    "  ud2\n"                     // Else crash.
#elif defined(__riscv)
#else
#error "what machine?"
#endif
    ".size ThreadEntry, . - ThreadEntry\n"
    ".popsection");

}  // namespace
