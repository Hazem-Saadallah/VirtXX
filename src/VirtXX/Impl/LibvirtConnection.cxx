#include <vector>
#include <cstdlib>
#include <numeric>
#include <functional>
#include <libvirt/libvirt.h>
#include <libvirt/virterror.h>
#include <VirtXX/Impl/ErrMsg.hxx>
#include <VirtXX/Impl/Misc.hxx>
#include <VirtXX/Impl/datatypes.hxx>
#include <VirtXX/Impl/LibvirtDomain.hxx>
#include <VirtXX/Impl/LibvirtStoragePool.hxx>
#include <VirtXX/Impl/LibvirtConnection.hxx>

VirtXX::Impl::LibvirtConnection::LibvirtConnection(virConnectPtr connection_ptr) : m_Handle(connection_ptr, Deleters::LibvirtConnectionPtrDeleter()) { }
VirtXX::Impl::LibvirtConnection::LibvirtConnection(const std::string& uri)
: m_Handle(virConnectOpen(uri.c_str()), Deleters::LibvirtConnectionPtrDeleter()), m_LastError(datatype::ErrorCode::NONE, ErrMsg::not_an_error) { }

VirtXX::Impl::LibvirtConnection::~LibvirtConnection() = default; /* defined in here becasue the unique poiter is initialized here.*/

VirtXX::Impl::LibvirtConnection::operator bool() const { return m_Handle != nullptr; }

void VirtXX::Impl::LibvirtConnection::report_error(datatype::ErrorCode code, datatype::ErrorMsg msg) {
  m_LastError = ErrorBlock(code, msg);
}

virConnectPtr VirtXX::Impl::LibvirtConnection::get_handle() const { return m_Handle.get(); }

VirtXX::Impl::ErrorBlock VirtXX::Impl::LibvirtConnection::get_last_error() const { return m_LastError; }

VirtXX::Impl::datatype::LibvirtInternalErrorPtr VirtXX::Impl::LibvirtConnection::get_last_libvirt_error() const {
  return datatype::LibvirtInternalErrorPtr(virSaveLastError(), Deleters::LibvirtErrorPtrDeleter());
}

std::int32_t VirtXX::Impl::LibvirtConnection::get_domain_count(std::vector<virConnectListAllDomainsFlags> flags) {
  std::int32_t count = virConnectListAllDomains(get_handle(), NULL, std::accumulate(flags.begin(), flags.end(), 0ULL,
                                                                                    std::bit_or<std::uint64_t>()));
  if(count < 0) report_error(datatype::ErrorCode::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error);
  return count;
}

VirtXX::Impl::datatype::DomainList VirtXX::Impl::LibvirtConnection::get_domains(std::vector<virConnectListAllDomainsFlags> flags) {
  virDomainPtr *domains = nullptr;
  std::int32_t domains_num = virConnectListAllDomains(get_handle(), &domains,
                                                      std::accumulate(flags.begin(), flags.end(),
                                                                      0ULL, std::bit_or<std::uint64_t>()));

  if(domains_num < 0) {
    report_error(datatype::ErrorCode::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error);
    return datatype::DomainList();
  }
  datatype::DomainList domains_vec;
  domains_vec.reserve(domains_num);

  for (std::int32_t i{0}; i < domains_num; ++i)
    domains_vec.emplace_back(LibvirtConnectionCreationKey{}, domains[i]);

  std::free(domains);
  return domains_vec;
}

VirtXX::Impl::LibvirtDomain VirtXX::Impl::LibvirtConnection::get_domain_by_id(std::int32_t id) const {
  return LibvirtDomain(LibvirtConnectionCreationKey{}, virDomainLookupByID(get_handle(), id));
}

VirtXX::Impl::LibvirtDomain VirtXX::Impl::LibvirtConnection::get_domain_by_name(const std::string& domain_name) const {
  return LibvirtDomain(LibvirtConnectionCreationKey{}, virDomainLookupByName(get_handle(), domain_name.c_str()));
}

VirtXX::Impl::LibvirtDomain VirtXX::Impl::LibvirtConnection::get_domain_by_uuid(const datatype::UUIDBytes& uuid) const {
  return LibvirtDomain(LibvirtConnectionCreationKey{}, virDomainLookupByUUID(get_handle(), uuid.data()));
}

VirtXX::Impl::LibvirtDomain VirtXX::Impl::LibvirtConnection::get_domain_by_uuid_string(const std::string& uuid_str) const {
  return LibvirtDomain(LibvirtConnectionCreationKey{}, virDomainLookupByUUIDString(get_handle(), uuid_str.data()));
}

std::int32_t VirtXX::Impl::LibvirtConnection::get_active_storage_pool_count() {
  return virConnectNumOfStoragePools(get_handle());
}

std::int32_t VirtXX::Impl::LibvirtConnection::get_defined_storage_pool_count() {
  return virConnectNumOfDefinedStoragePools(get_handle());
}

VirtXX::Impl::datatype::StoragePoolList VirtXX::Impl::LibvirtConnection::get_storage_pools(std::vector<virConnectListAllStoragePoolsFlags> flags) {
  virStoragePoolPtr *pools = nullptr;
  std::int32_t storage_pool_num = virConnectListAllStoragePools(get_handle(), &pools,
                                                                std::accumulate(flags.begin(), flags.end(),
                                                                                0UL, std::bit_or<std::uint64_t>()));
  if(storage_pool_num < 0) {
    report_error(datatype::ErrorCode::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error);
    return datatype::StoragePoolList();
  }

  datatype::StoragePoolList storage_pool_list;
  storage_pool_list.reserve(storage_pool_num);

  for(std::int32_t i{0}; i <storage_pool_num; ++i)
    storage_pool_list.emplace_back(LibvirtConnectionCreationKey{}, pools[i]);

  std::free(pools);
  return storage_pool_list;
}

VirtXX::Impl::LibvirtStoragePool VirtXX::Impl::LibvirtConnection::get_storage_pool_by_name(std::string name) {
  REPORT_AND_RETURN_IF_NULL_HANDLE(LibvirtStoragePool(LibvirtConnectionCreationKey{}, nullptr));
  virStoragePoolPtr pool = virStoragePoolLookupByName(get_handle(), name.c_str());
  if(!pool) report_error(datatype::ErrorCode::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error);
  return LibvirtStoragePool(LibvirtConnectionCreationKey{}, pool);
}

VirtXX::Impl::LibvirtStoragePool VirtXX::Impl::LibvirtConnection::get_storage_pool_by_target_path(std::string path) {
  REPORT_AND_RETURN_IF_NULL_HANDLE(LibvirtStoragePool(LibvirtConnectionCreationKey{}, nullptr));
  virStoragePoolPtr pool = virStoragePoolLookupByTargetPath(get_handle(), path.c_str());
  if(!pool) report_error(datatype::ErrorCode::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error);
  return LibvirtStoragePool(LibvirtConnectionCreationKey{}, pool);
}

VirtXX::Impl::LibvirtStoragePool VirtXX::Impl::LibvirtConnection::get_storage_pool_by_uuid_string(std::string uuid_str) {
  REPORT_AND_RETURN_IF_NULL_HANDLE(LibvirtStoragePool(LibvirtConnectionCreationKey{}, nullptr));
  virStoragePoolPtr pool = virStoragePoolLookupByUUIDString(get_handle(), uuid_str.c_str());
  if(!pool) report_error(datatype::ErrorCode::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error);
  return LibvirtStoragePool(LibvirtConnectionCreationKey{}, pool);
}

VirtXX::Impl::LibvirtStoragePool VirtXX::Impl::LibvirtConnection::get_storage_pool_by_uuid(datatype::UUIDBytes uuid) {
  REPORT_AND_RETURN_IF_NULL_HANDLE(LibvirtStoragePool(LibvirtConnectionCreationKey{}, nullptr));
  virStoragePoolPtr pool = virStoragePoolLookupByUUID(get_handle(), uuid.data());
  if(!pool) report_error(datatype::ErrorCode::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error);
  return LibvirtStoragePool(LibvirtConnectionCreationKey{}, pool);
}

VirtXX::Impl::LibvirtStorageVolume VirtXX::Impl::LibvirtConnection::get_volume_by_key(std::string key) {
  REPORT_AND_RETURN_IF_NULL_HANDLE(LibvirtStorageVolume(LibvirtConnectionCreationKey{}, nullptr));
  virStorageVolPtr volume = virStorageVolLookupByKey(get_handle(), key.c_str());
  if(!volume) report_error(datatype::ErrorCode::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error);
  return LibvirtStorageVolume(LibvirtConnectionCreationKey{}, volume);
}

VirtXX::Impl::LibvirtStorageVolume VirtXX::Impl::LibvirtConnection::get_volume_by_path(std::string path) {
  REPORT_AND_RETURN_IF_NULL_HANDLE(LibvirtStorageVolume(LibvirtConnectionCreationKey{}, nullptr));
  virStorageVolPtr volume = virStorageVolLookupByPath(get_handle(), path.c_str());
  if(!volume) report_error(datatype::ErrorCode::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error);
  return LibvirtStorageVolume(LibvirtConnectionCreationKey{}, volume);
}

VirtXX::Impl::LibvirtStoragePool VirtXX::Impl::LibvirtConnection::create_transient_storage_pool(const std::string& xml_config, std::vector< virStoragePoolCreateFlags> flags) {
  REPORT_AND_RETURN_IF_NULL_HANDLE(LibvirtStoragePool(LibvirtConnectionCreationKey{}, nullptr));
  virStoragePoolPtr pool = virStoragePoolCreateXML(get_handle(), xml_config.c_str(), std::accumulate(flags.begin(), flags.end(), 0, std::bit_or<std::uint64_t>()));
  if(!pool) report_error(datatype::ErrorCode::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error);
  return LibvirtStoragePool(LibvirtConnectionCreationKey{}, pool);
}

VirtXX::Impl::LibvirtStoragePool VirtXX::Impl::LibvirtConnection::create_persistent_storage_pool(const std::string& xml_config, std::vector<virStoragePoolDefineFlags> flags) {
  REPORT_AND_RETURN_IF_NULL_HANDLE(LibvirtStoragePool(LibvirtConnectionCreationKey{}, nullptr));
  virStoragePoolPtr pool = virStoragePoolDefineXML(get_handle(), xml_config.c_str(), std::accumulate(flags.begin(), flags.end(), 0, std::bit_or<std::uint64_t>()));
  if(!pool) report_error(datatype::ErrorCode::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error);
  return LibvirtStoragePool(LibvirtConnectionCreationKey{}, pool);
}
