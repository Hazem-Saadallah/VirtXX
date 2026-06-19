#pragma once

namespace VirtXX {
namespace Impl {
class LibvirtDomain;

class LibvirtDomainCreationKey {
  friend LibvirtDomain;

private:
  LibvirtDomainCreationKey() = default;

public:
  LibvirtDomainCreationKey(LibvirtDomainCreationKey &&) noexcept = default;
  LibvirtDomainCreationKey &operator=(LibvirtDomainCreationKey &&) noexcept = default;
  LibvirtDomainCreationKey(const LibvirtDomainCreationKey &) = default;
  LibvirtDomainCreationKey &operator=(const LibvirtDomainCreationKey &) = default;
  ~LibvirtDomainCreationKey() = default;
};
} /* Impl */
} /* VirtXX */
