#pragma once

namespace VirtXX {
namespace Impl {
class LibvirtConnection;

class LibvirtConnectionCreationKey {
  friend LibvirtConnection;

private:
  LibvirtConnectionCreationKey() = default;

public:
  LibvirtConnectionCreationKey (LibvirtConnectionCreationKey  &&) = default;
  LibvirtConnectionCreationKey (const LibvirtConnectionCreationKey  &) = default;
  LibvirtConnectionCreationKey &operator=(LibvirtConnectionCreationKey  &&) = default;
  LibvirtConnectionCreationKey &operator=(const LibvirtConnectionCreationKey  &) = default;
  ~LibvirtConnectionCreationKey () = default;
};
} /* Impl */
} /* VirtXX */
