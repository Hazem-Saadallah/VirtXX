#pragma once

#include <libvirt/libvirt.h>
#include <libvirt/virterror.h>

namespace VirtXX {
namespace Impl {
namespace Deleters {
class LibvirtConnectionPtrDeleter {
public:
  void operator()(virConnectPtr connection_ptr) const;
};

class LibvirtDomainPtrDeleter {
public:
  void operator()(virDomainPtr domain_ptr) const;
};

class LibvirtErrorPtrDeleter {
public:
  void operator()(virErrorPtr error_ptr) const;
};

class LibvirtStoragePoolPtrDeleter {
public:
  void operator()(virStoragePoolPtr storage_pool_ptr) const;
};

class LibvirtStorageVolumePtrDeleter {
public:
  void operator()(virStorageVolPtr storage_volume_ptr) const;
};
} /* Deleters */
} /* Impl */
} /* VirtXX */
