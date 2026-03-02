#pragma once

#include <ErrMsg.hxx>
#include <vector>
#include <libvirt/libvirt.h>
#include <datatypes.hxx>
#include <ErrorBlock.hxx>

class _LibvirtDomain;

class _LibvirtConnection {
friend _LibvirtDomain;
private:
  _datatype::_LibvirtInternalConnectionPtr m_ConnectionPtr;
  virError m_LastLibvirtError;
  _ErrorBlock m_LastError;
  // _datatype::_LibvirtInternalErrorPtr m_LastLibvirtError;

  void report_error(_datatype::ErrorCode_t code, _datatype::ErrorMsg_t msg);

public:
  explicit _LibvirtConnection(virConnectPtr connection_ptr);
  explicit _LibvirtConnection(const std::string& uri);
  ~_LibvirtConnection();
  _LibvirtConnection(_LibvirtConnection &&) = default;
  _LibvirtConnection &operator=(_LibvirtConnection &&) = default;
  _LibvirtConnection(const _LibvirtConnection &) = delete;
  _LibvirtConnection &operator=(const _LibvirtConnection &) = delete;

  explicit operator bool() const;

  [[nodiscard]] virConnectPtr get_handle() const;

  [[nodiscard]] _ErrorBlock get_last_error() const;
  [[nodiscard]] virError get_last_libvirt_error() const;

  [[nodiscard]] std::int32_t get_domain_count(std::vector<virConnectListAllDomainsFlags> flags={});
  [[nodiscard]] _LibvirtDomain get_domain_by_name(const std::string& domain_name) const;
};
