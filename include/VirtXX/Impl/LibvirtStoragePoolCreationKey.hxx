#pragma once

namespace VirtXX {
namespace Impl {
class LibvirtStoragePool;

class LibvirtStoragePoolCreationKey {
  friend LibvirtStoragePool;

private:
  LibvirtStoragePoolCreationKey() = default;

public:
  LibvirtStoragePoolCreationKey(LibvirtStoragePoolCreationKey &&) noexcept = default;
  LibvirtStoragePoolCreationKey &operator=(LibvirtStoragePoolCreationKey &&) noexcept = default;
  LibvirtStoragePoolCreationKey(const LibvirtStoragePoolCreationKey &) = default;
  LibvirtStoragePoolCreationKey &operator=(const LibvirtStoragePoolCreationKey &) = default;
  ~LibvirtStoragePoolCreationKey() = default;
};
} /* Impl */
} /* VirtXX */
