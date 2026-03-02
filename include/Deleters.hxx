#pragma once

#include <libvirt/libvirt.h>
#include <libvirt/virterror.h>

namespace Deleters {
  class _LibvirtConnectionPtrDeleter {
  public:
    void operator()(virConnectPtr connection_ptr) const;
  };

  class _LibvirtDomainPtrDeleter {
  public:
    void operator()(virDomainPtr domain_ptr) const;
  };

  class _LibvirtErrorPtrDeleter {
  public:
    void operator()(virErrorPtr error_ptr) const;
  };
}
