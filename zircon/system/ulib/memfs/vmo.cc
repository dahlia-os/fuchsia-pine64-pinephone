// Copyright 2017 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <fcntl.h>
#include <inttypes.h>
#include <lib/fdio/vfs.h>
#include <lib/memfs/cpp/vnode.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <zircon/device/vfs.h>

#include <fbl/algorithm.h>
#include <fbl/alloc_checker.h>
#include <fbl/ref_ptr.h>
#include <fs/vfs.h>
#include <fs/vfs_types.h>

#include "dnode.h"

namespace memfs {
namespace {

bool WindowMatchesVMO(zx_handle_t vmo, zx_off_t offset, zx_off_t length) {
  if (offset != 0)
    return false;
  uint64_t size;
  if (zx_vmo_get_size(vmo, &size) < 0)
    return false;
  return size == length;
}

}  // namespace

VnodeVmo::VnodeVmo(Vfs* vfs, zx_handle_t vmo, zx_off_t offset, zx_off_t length)
    : VnodeMemfs(vfs), vmo_(vmo), offset_(offset), length_(length), have_local_clone_(false) {}

VnodeVmo::~VnodeVmo() {
  if (have_local_clone_) {
    zx_handle_close(vmo_);
  }
}

fs::VnodeProtocolSet VnodeVmo::GetProtocols() const { return fs::VnodeProtocol::kMemory; }

bool VnodeVmo::ValidateRights(fs::Rights rights) { return !rights.write; }

zx_status_t VnodeVmo::GetNodeInfoForProtocol([[maybe_unused]] fs::VnodeProtocol protocol,
                                             [[maybe_unused]] fs::Rights rights,
                                             fs::VnodeRepresentation* info) {
  zx_info_handle_basic_t handle_info;
  zx_status_t status =
      zx_object_get_info(vmo_, ZX_INFO_HANDLE_BASIC, &handle_info, sizeof(handle_info), NULL, NULL);
  if (status != ZX_OK) {
    return status;
  }

  if (!have_local_clone_ && !WindowMatchesVMO(vmo_, offset_, length_)) {
    status = MakeLocalClone(handle_info.rights & ZX_RIGHT_EXECUTE);
    if (status != ZX_OK) {
      return status;
    }
  }

  // Drop write rights.
  zx_handle_t vmo;
  status =
      zx_handle_duplicate(vmo_,
                          ZX_RIGHT_READ | ZX_RIGHT_MAP | ZX_RIGHTS_BASIC | ZX_RIGHT_GET_PROPERTY |
                              (handle_info.rights & ZX_RIGHT_EXECUTE),  // Preserve exec if present.
                          &vmo);
  if (status != ZX_OK) {
    return status;
  }

  *info =
      fs::VnodeRepresentation::Memory{.vmo = zx::vmo(vmo), .offset = offset_, .length = length_};
  return ZX_OK;
}

zx_status_t VnodeVmo::Read(void* data, size_t len, size_t off, size_t* out_actual) {
  if (off > length_) {
    *out_actual = 0;
    return ZX_OK;
  }
  size_t rlen = length_ - off;
  if (len > rlen) {
    len = rlen;
  }
  zx_status_t status = zx_vmo_read(vmo_, data, offset_ + off, len);
  if (status == ZX_OK) {
    *out_actual = len;
  }
  return status;
}

zx_status_t VnodeVmo::GetAttributes(fs::VnodeAttributes* attr) {
  *attr = fs::VnodeAttributes();
  attr->inode = ino_;
  attr->mode = V_TYPE_FILE | V_IRUSR;
  attr->content_size = length_;
  attr->storage_size = fbl::round_up(attr->content_size, kMemfsBlksize);
  attr->link_count = link_count_;
  attr->creation_time = create_time_;
  attr->modification_time = modify_time_;
  return ZX_OK;
}

zx_status_t VnodeVmo::GetVmo(int flags, zx_handle_t* out_vmo, size_t* out_size) {
  if (!have_local_clone_ && !WindowMatchesVMO(vmo_, offset_, length_)) {
    zx_info_handle_basic_t handle_info;
    zx_status_t status = zx_object_get_info(vmo_, ZX_INFO_HANDLE_BASIC, &handle_info,
                                            sizeof(handle_info), NULL, NULL);
    if (status != ZX_OK) {
      return status;
    }
    status = MakeLocalClone(handle_info.rights & ZX_RIGHT_EXECUTE);
    if (status != ZX_OK) {
      return status;
    }
  }
  if (flags & fuchsia_io_VMO_FLAG_WRITE) {
    return ZX_ERR_NOT_SUPPORTED;
  }

  // Let clients map and set the names of their VMOs.
  zx_rights_t rights = ZX_RIGHTS_BASIC | ZX_RIGHT_MAP | ZX_RIGHTS_PROPERTY;
  // We can ignore fuchsia_io_VMO_FLAG_PRIVATE, since private / shared access
  // to the underlying VMO can both be satisfied due to the immutability of
  // Vmofiles.
  rights |= (flags & fuchsia_io_VMO_FLAG_READ) ? ZX_RIGHT_READ : 0;
  rights |= (flags & fuchsia_io_VMO_FLAG_EXEC) ? ZX_RIGHT_EXECUTE : 0;

  zx_handle_t vmo;
  zx_status_t status = zx_handle_duplicate(vmo_, rights, &vmo);
  if (status != ZX_OK) {
    return status;
  }

  *out_vmo = vmo;
  *out_size = length_;
  return ZX_OK;
}

zx_status_t VnodeVmo::MakeLocalClone(bool executable) {
  zx_handle_t tmp_vmo;
  zx_status_t status =
      zx_vmo_create_child(vmo_, ZX_VMO_CHILD_COPY_ON_WRITE, offset_, length_, &tmp_vmo);
  if (status != ZX_OK) {
    return status;
  }

  // Restore ZX_RIGHT_EXECUTE, if necessary.
  // TODO(mdempsky): Use non-COW clone once available.
  if (executable) {
    status = zx_vmo_replace_as_executable(tmp_vmo, ZX_HANDLE_INVALID, &vmo_);
    if (status != ZX_OK) {
      return status;
    }
  } else {
    vmo_ = tmp_vmo;
  }

  offset_ = 0;
  have_local_clone_ = true;
  return ZX_OK;
}

}  // namespace memfs
