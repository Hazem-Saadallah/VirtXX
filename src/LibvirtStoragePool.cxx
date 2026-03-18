#include <cstdlib>
#include <numeric>
#include <functional>
#include <libvirt/libvirt.h>
#include <ErrMsg.hxx>
#include <Misc.hxx>
#include <datatypes.hxx>
#include <LibvirtStoragePool.hxx>
#include <LibvirtConnectionCreationKey.hxx>
#include <vector>

_LibvirtStoragePool::_LibvirtStoragePool(_LibvirtConnectionCreationKey, virStoragePoolPtr storage_pool_ptr)
: m_Handle(storage_pool_ptr, Deleters::_LibvirtStoragePoolPtrDeleter()) {
  m_LastError = storage_pool_ptr
    ? _ErrorBlock(_datatype::ErrorCode_t::NONE, ErrMsg::not_an_error)
    : _ErrorBlock(_datatype::ErrorCode_t::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error);
}

_LibvirtStoragePool::~_LibvirtStoragePool() = default;

_LibvirtStoragePool::operator bool() const { return m_Handle != nullptr; }

bool _LibvirtStoragePool::is_active() {
  REPORT_AND_RETURN_IF_NULL_HANDLE(false);
  std::int32_t result = virStoragePoolIsActive(m_Handle.get());
  REPORT_AND_RETURN_IF_INTERNEL_ERROR(result, false);
  return static_cast<bool>(result);
}

void _LibvirtStoragePool::activate(std::vector<virStoragePoolCreateFlags> flags) {
  REPORT_AND_RETURN_IF_NULL_HANDLE();
  std::int32_t result = virStoragePoolCreate(m_Handle.get(), std::accumulate(flags.begin(), flags.end(), 0, std::bit_or<std::uint64_t>()));
  REPORT_AND_RETURN_IF_INTERNEL_ERROR(result,);
}

[[nodiscard]] bool _LibvirtStoragePool::is_auto_start() {
  REPORT_AND_RETURN_IF_NULL_HANDLE(false);
  std::int32_t autostart{0};
  std::int32_t result = virStoragePoolGetAutostart(get_handle(), &autostart);
  REPORT_AND_RETURN_IF_INTERNEL_ERROR(result, false);
  return autostart;
}

void _LibvirtStoragePool::set_auto_start(bool auto_start) {
  REPORT_AND_RETURN_IF_NULL_HANDLE();
  std::int32_t result = virStoragePoolSetAutostart(get_handle(), static_cast<std::int32_t>(auto_start));
  REPORT_AND_RETURN_IF_INTERNEL_ERROR(result, );
}

bool _LibvirtStoragePool::is_persistent() {
  REPORT_AND_RETURN_IF_NULL_HANDLE(false);
  std::int32_t result = virStoragePoolIsPersistent(m_Handle.get());
  REPORT_AND_RETURN_IF_INTERNEL_ERROR(result, false);
  return static_cast<bool>(result);
}

void _LibvirtStoragePool::make_persistent(std::vector<virStoragePoolBuildFlags> flags) {
  REPORT_AND_RETURN_IF_NULL_HANDLE();
  std::int32_t result = virStoragePoolBuild(m_Handle.get(), std::accumulate(flags.begin(), flags.end(), 0, std::bit_or<std::uint64_t>()));
  REPORT_AND_RETURN_IF_INTERNEL_ERROR(result,);
}

void _LibvirtStoragePool::report_error(_datatype::ErrorCode_t code, _datatype::ErrorMsg_t msg) {
  m_LastError = _ErrorBlock(code, msg);
}

[[nodiscard]] virStoragePoolPtr _LibvirtStoragePool::get_handle() const { return m_Handle.get(); }

std::string _LibvirtStoragePool::get_name() {
  REPORT_AND_RETURN_IF_NULL_HANDLE(std::string());
  const char* buffer = virStoragePoolGetName(get_handle());
  if(!buffer) return std::string();
  return std::string(buffer);
}

std::string _LibvirtStoragePool::get_uuid_string() {
  REPORT_AND_RETURN_IF_NULL_HANDLE(std::string());
  std::string buffer(VIR_UUID_STRING_BUFLEN, '\0');
  std::int32_t result = virStoragePoolGetUUIDString(get_handle(), buffer.data());
  REPORT_AND_RETURN_IF_INTERNEL_ERROR(result, std::string());
  return buffer;
}

_datatype::_UUIDBytes _LibvirtStoragePool::get_uuid() {
  REPORT_AND_RETURN_IF_NULL_HANDLE(_datatype::_UUIDBytes());
  _datatype::_UUIDBytes buffer = {0};
  std::int32_t result = virStoragePoolGetUUID(get_handle(), buffer.data());
  REPORT_AND_RETURN_IF_INTERNEL_ERROR(result, _datatype::_UUIDBytes());
  return buffer;
}

std::string _LibvirtStoragePool::get_xml_config(std::vector<virStorageXMLFlags> flags) {
  REPORT_AND_RETURN_IF_NULL_HANDLE(std::string());
  char *raw_xml = virStoragePoolGetXMLDesc(get_handle(), std::accumulate(flags.begin(), flags.end(),
                                                                               0UL, std::bit_or<std::uint64_t>()));
  if(!raw_xml) return std::string();
  std::string config = std::string(raw_xml);
  std::free(raw_xml);
  return config;
}

std::int32_t _LibvirtStoragePool::get_num_of_volumes() {
  REPORT_AND_RETURN_IF_NULL_HANDLE(std::int32_t());
  std::int32_t result = virStoragePoolNumOfVolumes(get_handle());
  REPORT_AND_RETURN_IF_INTERNEL_ERROR(result, std::int32_t());
  return result;
}

_LibvirtStorageVolume _LibvirtStoragePool::get_volume_by_name(std::string name) {
  REPORT_AND_RETURN_IF_NULL_HANDLE(_LibvirtStorageVolume(_LibvirtStoragePoolCreationKey{}, nullptr));
  virStorageVolPtr result = virStorageVolLookupByName(get_handle(), name.c_str());
  if(!result) return _LibvirtStorageVolume(_LibvirtStoragePoolCreationKey{}, nullptr);
  return _LibvirtStorageVolume(_LibvirtStoragePoolCreationKey{}, result);
}

_datatype::_StorageVolumeList _LibvirtStoragePool::get_volumes() {
  REPORT_AND_RETURN_IF_NULL_HANDLE(_datatype::_StorageVolumeList());

  virStorageVolPtr *volumes = nullptr;
  std::int32_t storage_volume_num = virStoragePoolListAllVolumes(get_handle(), &volumes, 0);

  if(storage_volume_num < 0) {
    report_error(_datatype::ErrorCode_t::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error);
    return _datatype::_StorageVolumeList();
  }
  _datatype::_StorageVolumeList storage_volume_list;
  storage_volume_list.reserve(storage_volume_num);

  for(std::int32_t i{0}; i < storage_volume_num; ++i)
    storage_volume_list.emplace_back(_LibvirtStoragePoolCreationKey{}, volumes[i]);

  std::free(volumes);
  return storage_volume_list;
}

_LibvirtStorageVolume _LibvirtStoragePool::create_storage_volume(const std::string& xml_config, std::vector<virStorageVolCreateFlags> flags) {
  REPORT_AND_RETURN_IF_NULL_HANDLE(_LibvirtStorageVolume(_LibvirtStoragePoolCreationKey{}, nullptr));
  virStorageVolPtr volume = virStorageVolCreateXML(get_handle(), xml_config.c_str(), std::accumulate(flags.begin(), flags.end(), 0, std::bit_or<std::uint64_t>()));
  if(!volume) report_error(_datatype::ErrorCode_t::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error);
  return _LibvirtStorageVolume(_LibvirtStoragePoolCreationKey{}, volume);
}

_LibvirtStorageVolume _LibvirtStoragePool::clone_storage_volume(_LibvirtStorageVolume volume, const std::string& xml_config, std::vector<virStorageVolCreateFlags> flags) {
  REPORT_AND_RETURN_IF_NULL_HANDLE(_LibvirtStorageVolume(_LibvirtStoragePoolCreationKey{}, nullptr));
  if(!volume) {
    report_error(_datatype::ErrorCode_t::NULL_DOMAIN_PTR , ErrMsg::null_domain_ptr);
    return _LibvirtStorageVolume(_LibvirtStoragePoolCreationKey{}, nullptr);
  }
  virStorageVolPtr vol =  virStorageVolCreateXMLFrom(get_handle(), xml_config.c_str(), volume.get_handle(), std::accumulate(flags.begin(), flags.end(), 0, std::bit_or<std::uint64_t>()));
  if(!vol) report_error(_datatype::ErrorCode_t::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error);
  return _LibvirtStorageVolume(_LibvirtStoragePoolCreationKey{}, vol);
}
