#pragma once

class _LibvirtConnection;

class _LibvirtConnectionCreationKey {
  friend _LibvirtConnection;

private:
  _LibvirtConnectionCreationKey() = default;

public:
  _LibvirtConnectionCreationKey (_LibvirtConnectionCreationKey  &&) = default;
  _LibvirtConnectionCreationKey (const _LibvirtConnectionCreationKey  &) = default;
  _LibvirtConnectionCreationKey &operator=(_LibvirtConnectionCreationKey  &&) = default;
  _LibvirtConnectionCreationKey &operator=(const _LibvirtConnectionCreationKey  &) = default;
  ~_LibvirtConnectionCreationKey () = default;
};

