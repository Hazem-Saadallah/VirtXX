#pragma once

class _LibvirtStoragePool;

class _LibvirtStoragePoolCreationKey {
  friend _LibvirtStoragePool;

private:
  _LibvirtStoragePoolCreationKey() = default;

public:
  _LibvirtStoragePoolCreationKey(_LibvirtStoragePoolCreationKey &&) noexcept = default;
  _LibvirtStoragePoolCreationKey &operator=(_LibvirtStoragePoolCreationKey &&) noexcept = default;
  _LibvirtStoragePoolCreationKey(const _LibvirtStoragePoolCreationKey &) = default;
  _LibvirtStoragePoolCreationKey &operator=(const _LibvirtStoragePoolCreationKey &) = default;
  ~_LibvirtStoragePoolCreationKey() = default;
};
