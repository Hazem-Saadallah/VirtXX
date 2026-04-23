#pragma once

#include <vector>
#include <libvirt/libvirt.h>
#include <VirtXX/Impl/ErrMsg.hxx>
#include <VirtXX/Impl/datatypes.hxx>
#include <VirtXX/Impl/ErrorBlock.hxx>
#include <VirtXX/Impl/datatypes.hxx>
#include <VirtXX/Impl/LibvirtDomain.hxx>
#include <VirtXX/Impl/LibvirtStoragePool.hxx>

namespace VirtXX {
  namespace Impl {
    class LibvirtConnection {
    friend LibvirtDomain;
    private:
      datatype::LibvirtInternalConnectionPtr m_Handle;
      ErrorBlock m_LastError;

      void report_error(datatype::ErrorCode code, datatype::ErrorMsg msg);

    public:
      explicit LibvirtConnection(virConnectPtr connection_ptr);
      explicit LibvirtConnection(const std::string& uri);
      ~LibvirtConnection();
      LibvirtConnection(LibvirtConnection &&) noexcept = default;
      LibvirtConnection &operator=(LibvirtConnection &&) noexcept = default;
      LibvirtConnection(const LibvirtConnection &) = default;
      LibvirtConnection &operator=(const LibvirtConnection &) = default;

      explicit operator bool() const;

      [[nodiscard]] virConnectPtr get_handle() const;

      [[nodiscard]] ErrorBlock get_last_error() const;
      [[nodiscard]] datatype::LibvirtInternalErrorPtr get_last_libvirt_error() const;

      [[nodiscard]] std::int32_t get_domain_count(std::vector<virConnectListAllDomainsFlags> flags={});
      [[nodiscard]] datatype::DomainList get_domains(std::vector<virConnectListAllDomainsFlags> flags={});
      [[nodiscard]] LibvirtDomain get_domain_by_id(std::int32_t id) const;
      [[nodiscard]] LibvirtDomain get_domain_by_name(const std::string& domain_name) const;
      [[nodiscard]] LibvirtDomain get_domain_by_uuid(const datatype::UUIDBytes& uuid) const;
      [[nodiscard]] LibvirtDomain get_domain_by_uuid_string(const std::string& uuid_str) const;

      [[nodiscard]] std::int32_t get_active_storage_pool_count();
      [[nodiscard]] std::int32_t get_defined_storage_pool_count();
      [[nodiscard]] datatype::StoragePoolList get_storage_pools(std::vector<virConnectListAllStoragePoolsFlags> flags={});

      [[nodiscard]] LibvirtStoragePool get_storage_pool_by_name(std::string name);
      [[nodiscard]] LibvirtStoragePool get_storage_pool_by_target_path(std::string path);
      [[nodiscard]] LibvirtStoragePool get_storage_pool_by_uuid_string(std::string uuid_str);
      [[nodiscard]] LibvirtStoragePool get_storage_pool_by_uuid(datatype::UUIDBytes uuid);

      [[nodiscard]] LibvirtStorageVolume get_volume_by_key(std::string key);
      [[nodiscard]] LibvirtStorageVolume get_volume_by_path(std::string path);

      [[nodiscard]] LibvirtStoragePool create_transient_storage_pool(const std::string& xml_config, std::vector<virStoragePoolCreateFlags> flags);
      [[nodiscard]] LibvirtStoragePool create_persistent_storage_pool(const std::string& xml_config, std::vector<virStoragePoolDefineFlags> flags);
    };
  }
}
