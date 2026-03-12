#pragma once

#include <vector>
#include <libvirt/libvirt.h>
#include <ErrMsg.hxx>
#include <datatypes.hxx>
#include <ErrorBlock.hxx>
#include <datatypes.hxx>
#include <LibvirtDomain.hxx>
#include <LibvirtStoragePool.hxx>

class _LibvirtConnection {
friend _LibvirtDomain;
private:
  _datatype::_LibvirtInternalConnectionPtr m_ConnectionPtr;
  _ErrorBlock m_LastError;

  void report_error(_datatype::ErrorCode_t code, _datatype::ErrorMsg_t msg);

public:
  explicit _LibvirtConnection(virConnectPtr connection_ptr);
  explicit _LibvirtConnection(const std::string& uri);
  ~_LibvirtConnection();
  _LibvirtConnection(_LibvirtConnection &&) noexcept = default;
  _LibvirtConnection &operator=(_LibvirtConnection &&) noexcept = default;
  _LibvirtConnection(const _LibvirtConnection &) = delete;
  _LibvirtConnection &operator=(const _LibvirtConnection &) = delete;

  explicit operator bool() const;

  [[nodiscard]] virConnectPtr get_handle() const;

  [[nodiscard]] _ErrorBlock get_last_error() const;
  [[nodiscard]] _datatype::_LibvirtInternalErrorPtr get_last_libvirt_error() const;

  [[nodiscard]] std::int32_t get_domain_count(std::vector<virConnectListAllDomainsFlags> flags={});
  [[nodiscard]] _datatype::_DomainList get_domains(std::vector<virConnectListAllDomainsFlags> flags={});
  [[nodiscard]] _LibvirtDomain get_domain_by_id(std::int32_t id) const;
  [[nodiscard]] _LibvirtDomain get_domain_by_name(const std::string& domain_name) const;

  [[nodiscard]] std::int32_t get_active_storage_pool_count();
  [[nodiscard]] std::int32_t get_defined_storage_pool_count();
  [[nodiscard]] _datatype::_StoragePoolList get_storage_pools(std::vector<virConnectListAllStoragePoolsFlags> flags={});

  [[nodiscard]] _LibvirtStoragePool get_storage_pool_by_name(std::string name);
  [[nodiscard]] _LibvirtStoragePool get_storage_pool_by_target_path(std::string path);
  [[nodiscard]] _LibvirtStoragePool get_storage_pool_by_uuid_string(std::string uuid_str);
  [[nodiscard]] _LibvirtStoragePool get_storage_pool_by_uuid(_datatype::_UUIDBytes uuid);

  [[nodiscard]] _LibvirtStorageVolume get_volume_by_key(std::string key);
  [[nodiscard]] _LibvirtStorageVolume get_volume_by_path(std::string path);

  [[nodiscard]] _LibvirtStoragePool create_transient_storage_pool(const std::string& xml_config, std::vector<virStoragePoolCreateFlags> flags);
  [[nodiscard]] _LibvirtStoragePool create_persistent_storage_pool(const std::string& xml_config, std::vector<virStoragePoolDefineFlags> flags);
};
