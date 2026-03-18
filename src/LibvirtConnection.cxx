#include <vector>
#include <cstdlib>
#include <numeric>
#include <functional>
#include <libvirt/libvirt.h>
#include <libvirt/virterror.h>
#include <ErrMsg.hxx>
#include <Misc.hxx>
#include <datatypes.hxx>
#include <LibvirtDomain.hxx>
#include <LibvirtStoragePool.hxx>
#include <LibvirtConnection.hxx>

_LibvirtConnection::_LibvirtConnection(virConnectPtr connection_ptr) : m_Handle(connection_ptr, Deleters::_LibvirtConnectionPtrDeleter()) { }
_LibvirtConnection::_LibvirtConnection(const std::string& uri)
: m_Handle(virConnectOpen(uri.c_str()), Deleters::_LibvirtConnectionPtrDeleter()), m_LastError(_datatype::ErrorCode_t::NONE, ErrMsg::not_an_error) { }

_LibvirtConnection::~_LibvirtConnection() = default; /* defined in here becasue the unique poiter is initialized here.*/

_LibvirtConnection::operator bool() const { return m_Handle != nullptr; }

void _LibvirtConnection::report_error(_datatype::ErrorCode_t code, _datatype::ErrorMsg_t msg) {
  m_LastError = _ErrorBlock(code, msg);
}

virConnectPtr _LibvirtConnection::get_handle() const { return m_Handle.get(); }

_ErrorBlock _LibvirtConnection::get_last_error() const { return m_LastError; }
_datatype::_LibvirtInternalErrorPtr _LibvirtConnection::get_last_libvirt_error() const {
  return _datatype::_LibvirtInternalErrorPtr(virSaveLastError(), Deleters::_LibvirtErrorPtrDeleter());
}

std::int32_t _LibvirtConnection::get_domain_count(std::vector<virConnectListAllDomainsFlags> flags) {
  std::int32_t count = virConnectListAllDomains(get_handle(), NULL, std::accumulate(flags.begin(), flags.end(), 0ULL,
                                                                                    std::bit_or<std::uint64_t>()));
  if(count < 0) report_error(_datatype::ErrorCode_t::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error);
  return count;
}

_datatype::_DomainList _LibvirtConnection::get_domains(std::vector<virConnectListAllDomainsFlags> flags) {
  virDomainPtr *domains = nullptr;
  std::int32_t domains_num = virConnectListAllDomains(get_handle(), &domains,
                                                      std::accumulate(flags.begin(), flags.end(),
                                                                      0ULL, std::bit_or<std::uint64_t>()));

  if(domains_num < 0) {
    report_error(_datatype::ErrorCode_t::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error);
    return _datatype::_DomainList();
  }
  _datatype::_DomainList domains_vec;
  domains_vec.reserve(domains_num);

  for (std::int32_t i{0}; i < domains_num; ++i)
    domains_vec.emplace_back(_LibvirtConnectionCreationKey{}, domains[i]);

  std::free(domains);
  return domains_vec;
}

_LibvirtDomain _LibvirtConnection::get_domain_by_id(std::int32_t id) const {
  return _LibvirtDomain(_LibvirtConnectionCreationKey{}, virDomainLookupByID(get_handle(), id));
}

_LibvirtDomain _LibvirtConnection::get_domain_by_name(const std::string& domain_name) const {
  return _LibvirtDomain(_LibvirtConnectionCreationKey{}, virDomainLookupByName(get_handle(), domain_name.c_str()));
}

std::int32_t _LibvirtConnection::get_active_storage_pool_count() {
  return virConnectNumOfStoragePools(get_handle());
}

std::int32_t _LibvirtConnection::get_defined_storage_pool_count() {
  return virConnectNumOfDefinedStoragePools(get_handle());
}

_datatype::_StoragePoolList _LibvirtConnection::get_storage_pools(std::vector<virConnectListAllStoragePoolsFlags> flags) {
  virStoragePoolPtr *pools = nullptr;
  std::int32_t storage_pool_num = virConnectListAllStoragePools(get_handle(), &pools,
                                                                std::accumulate(flags.begin(), flags.end(),
                                                                                0UL, std::bit_or<std::uint64_t>()));
  if(storage_pool_num < 0) {
    report_error(_datatype::ErrorCode_t::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error);
    return _datatype::_StoragePoolList();
  }

  _datatype::_StoragePoolList storage_pool_list;
  storage_pool_list.reserve(storage_pool_num);

  for(std::int32_t i{0}; i <storage_pool_num; ++i)
    storage_pool_list.emplace_back(_LibvirtConnectionCreationKey{}, pools[i]);

  std::free(pools);
  return storage_pool_list;
}

_LibvirtStoragePool _LibvirtConnection::get_storage_pool_by_name(std::string name) {
  REPORT_AND_RETURN_IF_NULL_HANDLE(_LibvirtStoragePool(_LibvirtConnectionCreationKey{}, nullptr));
  virStoragePoolPtr pool = virStoragePoolLookupByName(get_handle(), name.c_str());
  if(!pool) report_error(_datatype::ErrorCode_t::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error);
  return _LibvirtStoragePool(_LibvirtConnectionCreationKey{}, pool);
}

_LibvirtStoragePool _LibvirtConnection::get_storage_pool_by_target_path(std::string path) {
  REPORT_AND_RETURN_IF_NULL_HANDLE(_LibvirtStoragePool(_LibvirtConnectionCreationKey{}, nullptr));
  virStoragePoolPtr pool = virStoragePoolLookupByTargetPath(get_handle(), path.c_str());
  if(!pool) report_error(_datatype::ErrorCode_t::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error);
  return _LibvirtStoragePool(_LibvirtConnectionCreationKey{}, pool);
}

_LibvirtStoragePool _LibvirtConnection::get_storage_pool_by_uuid_string(std::string uuid_str) {
  REPORT_AND_RETURN_IF_NULL_HANDLE(_LibvirtStoragePool(_LibvirtConnectionCreationKey{}, nullptr));
  virStoragePoolPtr pool = virStoragePoolLookupByUUIDString(get_handle(), uuid_str.c_str());
  if(!pool) report_error(_datatype::ErrorCode_t::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error);
  return _LibvirtStoragePool(_LibvirtConnectionCreationKey{}, pool);
}

_LibvirtStoragePool _LibvirtConnection::get_storage_pool_by_uuid(_datatype::_UUIDBytes uuid) {
  REPORT_AND_RETURN_IF_NULL_HANDLE(_LibvirtStoragePool(_LibvirtConnectionCreationKey{}, nullptr));
  virStoragePoolPtr pool = virStoragePoolLookupByUUID(get_handle(), uuid.data());
  if(!pool) report_error(_datatype::ErrorCode_t::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error);
  return _LibvirtStoragePool(_LibvirtConnectionCreationKey{}, pool);
}

_LibvirtStorageVolume _LibvirtConnection::get_volume_by_key(std::string key) {
  REPORT_AND_RETURN_IF_NULL_HANDLE(_LibvirtStorageVolume(_LibvirtConnectionCreationKey{}, nullptr));
  virStorageVolPtr volume = virStorageVolLookupByKey(get_handle(), key.c_str());
  if(!volume) report_error(_datatype::ErrorCode_t::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error);
  return _LibvirtStorageVolume(_LibvirtConnectionCreationKey{}, volume);
}

_LibvirtStorageVolume _LibvirtConnection::get_volume_by_path(std::string path) {
  REPORT_AND_RETURN_IF_NULL_HANDLE(_LibvirtStorageVolume(_LibvirtConnectionCreationKey{}, nullptr));
  virStorageVolPtr volume = virStorageVolLookupByPath(get_handle(), path.c_str());
  if(!volume) report_error(_datatype::ErrorCode_t::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error);
  return _LibvirtStorageVolume(_LibvirtConnectionCreationKey{}, volume);
}

_LibvirtStoragePool _LibvirtConnection::create_transient_storage_pool(const std::string& xml_config, std::vector< virStoragePoolCreateFlags> flags) {
  REPORT_AND_RETURN_IF_NULL_HANDLE(_LibvirtStoragePool(_LibvirtConnectionCreationKey{}, nullptr));
  virStoragePoolPtr pool = virStoragePoolCreateXML(get_handle(), xml_config.c_str(), std::accumulate(flags.begin(), flags.end(), 0, std::bit_or<std::uint64_t>()));
  if(!pool) report_error(_datatype::ErrorCode_t::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error);
  return _LibvirtStoragePool(_LibvirtConnectionCreationKey{}, pool);
}

_LibvirtStoragePool _LibvirtConnection::create_persistent_storage_pool(const std::string& xml_config, std::vector<virStoragePoolDefineFlags> flags) {
  REPORT_AND_RETURN_IF_NULL_HANDLE(_LibvirtStoragePool(_LibvirtConnectionCreationKey{}, nullptr));
  virStoragePoolPtr pool = virStoragePoolDefineXML(get_handle(), xml_config.c_str(), std::accumulate(flags.begin(), flags.end(), 0, std::bit_or<std::uint64_t>()));
  if(!pool) report_error(_datatype::ErrorCode_t::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error);
  return _LibvirtStoragePool(_LibvirtConnectionCreationKey{}, pool);
}
