#include <cmath>
#include <cstdlib>
#include <numeric>
#include <functional>
#include <libvirt/libvirt.h>
#include <VirtXX/Impl/ErrMsg.hxx>
#include <VirtXX/Impl/Misc.hxx>
#include <VirtXX/Impl/datatypes.hxx>
#include <VirtXX/Impl/LibvirtStoragePool.hxx>
#include <VirtXX/Impl/LibvirtConnectionCreationKey.hxx>
#include <vector>

VirtXX::Impl::LibvirtStoragePool::LibvirtStoragePool(LibvirtConnectionCreationKey, virStoragePoolPtr storage_pool_ptr)
: m_Handle(storage_pool_ptr, Deleters::LibvirtStoragePoolPtrDeleter()) {
  m_LastError = storage_pool_ptr
    ? ErrorBlock(datatype::ErrorCode::NONE, ErrMsg::not_an_error)
    : ErrorBlock(datatype::ErrorCode::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error);
}

VirtXX::Impl::LibvirtStoragePool::~LibvirtStoragePool() = default;

VirtXX::Impl::LibvirtStoragePool::operator bool() const { return m_Handle != nullptr; }

bool VirtXX::Impl::LibvirtStoragePool::is_active() {
  REPORT_AND_RETURN_IF_NULL_HANDLE(false);
  std::int32_t result = virStoragePoolIsActive(m_Handle.get());
  REPORT_AND_RETURN_IF_INTERNEL_ERROR(result, false);
  return static_cast<bool>(result);
}

void VirtXX::Impl::LibvirtStoragePool::activate(std::vector<virStoragePoolCreateFlags> flags) {
  REPORT_AND_RETURN_IF_NULL_HANDLE();
  std::int32_t result = virStoragePoolCreate(m_Handle.get(), std::accumulate(flags.begin(), flags.end(), static_cast<std::uint64_t>(VIR_STORAGE_POOL_CREATE_NORMAL), std::bit_or<std::uint64_t>()));
  REPORT_AND_RETURN_IF_INTERNEL_ERROR(result,);
}

void VirtXX::Impl::LibvirtStoragePool::destroy() {
  REPORT_AND_RETURN_IF_NULL_HANDLE();
  std::int32_t result = virStoragePoolDestroy(get_handle());
  REPORT_AND_RETURN_IF_INTERNEL_ERROR(result, );
}

void VirtXX::Impl::LibvirtStoragePool::deactivate() { destroy(); }

void VirtXX::Impl::LibvirtStoragePool::set_activation(bool active) { active? activate():destroy(); }

bool VirtXX::Impl::LibvirtStoragePool::is_auto_start() {
  REPORT_AND_RETURN_IF_NULL_HANDLE(false);
  std::int32_t autostart{0};
  std::int32_t result = virStoragePoolGetAutostart(get_handle(), &autostart);
  REPORT_AND_RETURN_IF_INTERNEL_ERROR(result, false);
  return autostart;
}

void VirtXX::Impl::LibvirtStoragePool::set_auto_start(bool auto_start) {
  REPORT_AND_RETURN_IF_NULL_HANDLE();
  std::int32_t result = virStoragePoolSetAutostart(get_handle(), static_cast<std::int32_t>(auto_start));
  REPORT_AND_RETURN_IF_INTERNEL_ERROR(result, );
}

bool VirtXX::Impl::LibvirtStoragePool::is_persistent() {
  REPORT_AND_RETURN_IF_NULL_HANDLE(false);
  std::int32_t result = virStoragePoolIsPersistent(m_Handle.get());
  REPORT_AND_RETURN_IF_INTERNEL_ERROR(result, false);
  return static_cast<bool>(result);
}

void VirtXX::Impl::LibvirtStoragePool::make_persistent(std::vector<virStoragePoolBuildFlags> flags) {
  REPORT_AND_RETURN_IF_NULL_HANDLE();
  std::int32_t result = virStoragePoolBuild(m_Handle.get(), std::accumulate(flags.begin(), flags.end(), 0, std::bit_or<std::uint64_t>()));
  REPORT_AND_RETURN_IF_INTERNEL_ERROR(result,);
}

void VirtXX::Impl::LibvirtStoragePool::undefine() {
  REPORT_AND_RETURN_IF_NULL_HANDLE();
  std::int32_t result = virStoragePoolUndefine(get_handle());
  REPORT_AND_RETURN_IF_INTERNEL_ERROR(result,);
}

void VirtXX::Impl::LibvirtStoragePool::refresh() {
  REPORT_AND_RETURN_IF_NULL_HANDLE();
  std::int32_t result = virStoragePoolRefresh(get_handle(), 0);
  REPORT_AND_RETURN_IF_INTERNEL_ERROR(result, );
}

void VirtXX::Impl::LibvirtStoragePool::report_error(datatype::ErrorCode code, datatype::ErrorMsg msg) const {
  m_LastError = ErrorBlock(code, msg);
}

[[nodiscard]] virStoragePoolPtr VirtXX::Impl::LibvirtStoragePool::get_handle() const { return m_Handle.get(); }

std::string VirtXX::Impl::LibvirtStoragePool::get_name() const {
  REPORT_AND_RETURN_IF_NULL_HANDLE(std::string());
  const char* buffer = virStoragePoolGetName(get_handle());
  if(!buffer) return std::string();
  return std::string(buffer);
}

std::string VirtXX::Impl::LibvirtStoragePool::get_uuid_string() const {
  REPORT_AND_RETURN_IF_NULL_HANDLE(std::string());
  std::string buffer(VIR_UUID_STRING_BUFLEN, '\0');
  std::int32_t result = virStoragePoolGetUUIDString(get_handle(), buffer.data());
  REPORT_AND_RETURN_IF_INTERNEL_ERROR(result, std::string());
  return buffer;
}

VirtXX::Impl::datatype::UUIDBytes VirtXX::Impl::LibvirtStoragePool::get_uuid() const {
  REPORT_AND_RETURN_IF_NULL_HANDLE(datatype::UUIDBytes());
  datatype::UUIDBytes buffer = {0};
  std::int32_t result = virStoragePoolGetUUID(get_handle(), buffer.data());
  REPORT_AND_RETURN_IF_INTERNEL_ERROR(result, datatype::UUIDBytes());
  return buffer;
}

std::string VirtXX::Impl::LibvirtStoragePool::get_xml_config(std::vector<virStorageXMLFlags> flags) const {
  REPORT_AND_RETURN_IF_NULL_HANDLE(std::string());
  char *raw_xml = virStoragePoolGetXMLDesc(get_handle(), std::accumulate(flags.begin(), flags.end(),
                                                                               0UL, std::bit_or<std::uint64_t>()));
  if(!raw_xml) return std::string();
  std::string config = std::string(raw_xml);
  std::free(raw_xml);
  return config;
}

virStoragePoolInfo VirtXX::Impl::LibvirtStoragePool::get_info() const {
  REPORT_AND_RETURN_IF_NULL_HANDLE(virStoragePoolInfo{});
  virStoragePoolInfo info;
  std::int32_t result = virStoragePoolGetInfo(get_handle(), &info);
  REPORT_AND_RETURN_IF_INTERNEL_ERROR(result, virStoragePoolInfo{});
  return info;
}

virStoragePoolState VirtXX::Impl::LibvirtStoragePool::get_state() const {
  virStoragePoolInfo info = get_info();
  return static_cast<virStoragePoolState>(info.state);
}

std::string VirtXX::Impl::LibvirtStoragePool::get_state_string() const {
  switch (get_state()) {
    case VIR_STORAGE_POOL_INACTIVE: return std::string("Inactive"); break;
    case VIR_STORAGE_POOL_BUILDING: return std::string("Building"); break;
    case VIR_STORAGE_POOL_RUNNING: return std::string("Running"); break;
    case VIR_STORAGE_POOL_DEGRADED: return std::string("Degraded"); break;
    case VIR_STORAGE_POOL_INACCESSIBLE: return std::string("Inaccessible"); break;

# ifdef VIR_ENUM_SENTINELS
    case VIR_STORAGE_POOL_STATE_LAST: return std::string("Last"); break;
# endif
  }
  return std::string("Unknown");
}

std::double_t VirtXX::Impl::LibvirtStoragePool::get_capacity(SizeType size_type) const {
  std::double_t div = std::powf(1024, static_cast<std::int32_t>(size_type));
  return static_cast<std::double_t>(get_info().capacity)/div;
}

std::double_t VirtXX::Impl::LibvirtStoragePool::get_allocated_space(SizeType size_type) const {
  std::double_t div = std::powf(1024, static_cast<std::int32_t>(size_type));
  return static_cast<std::double_t>(get_info().allocation)/div;
}

std::double_t VirtXX::Impl::LibvirtStoragePool::get_available_space(SizeType size_type) const {
  std::double_t div = std::powf(1024, static_cast<std::int32_t>(size_type));
  return static_cast<std::double_t>(get_info().available)/div;
}

std::int32_t VirtXX::Impl::LibvirtStoragePool::get_num_of_volumes() const {
  REPORT_AND_RETURN_IF_NULL_HANDLE(std::int32_t());
  std::int32_t result = virStoragePoolNumOfVolumes(get_handle());
  REPORT_AND_RETURN_IF_INTERNEL_ERROR(result, std::int32_t());
  return result;
}

VirtXX::Impl::LibvirtStorageVolume VirtXX::Impl::LibvirtStoragePool::get_volume_by_name(std::string name) const {
  REPORT_AND_RETURN_IF_NULL_HANDLE(LibvirtStorageVolume(LibvirtStoragePoolCreationKey{}, nullptr));
  virStorageVolPtr result = virStorageVolLookupByName(get_handle(), name.c_str());
  if(!result) return LibvirtStorageVolume(LibvirtStoragePoolCreationKey{}, nullptr);
  return LibvirtStorageVolume(LibvirtStoragePoolCreationKey{}, result);
}

VirtXX::Impl::datatype::StorageVolumeList VirtXX::Impl::LibvirtStoragePool::get_volumes() const {
  REPORT_AND_RETURN_IF_NULL_HANDLE(datatype::StorageVolumeList());

  virStorageVolPtr *volumes = nullptr;
  std::int32_t storage_volume_num = virStoragePoolListAllVolumes(get_handle(), &volumes, 0);

  if(storage_volume_num < 0) {
    report_error(datatype::ErrorCode::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error);
    return datatype::StorageVolumeList();
  }
  datatype::StorageVolumeList storage_volume_list;
  storage_volume_list.reserve(storage_volume_num);

  for(std::int32_t i{0}; i < storage_volume_num; ++i)
    storage_volume_list.emplace_back(LibvirtStoragePoolCreationKey{}, volumes[i]);

  std::free(volumes);
  return storage_volume_list;
}

VirtXX::Impl::LibvirtStorageVolume VirtXX::Impl::LibvirtStoragePool::create_storage_volume(const std::string& xml_config, std::vector<virStorageVolCreateFlags> flags) {
  REPORT_AND_RETURN_IF_NULL_HANDLE(LibvirtStorageVolume(LibvirtStoragePoolCreationKey{}, nullptr));
  virStorageVolPtr volume = virStorageVolCreateXML(get_handle(), xml_config.c_str(), std::accumulate(flags.begin(), flags.end(), 0, std::bit_or<std::uint64_t>()));
  if(!volume) report_error(datatype::ErrorCode::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error);
  return LibvirtStorageVolume(LibvirtStoragePoolCreationKey{}, volume);
}

VirtXX::Impl::LibvirtStorageVolume VirtXX::Impl::LibvirtStoragePool::clone_storage_volume(LibvirtStorageVolume volume, const std::string& xml_config, std::vector<virStorageVolCreateFlags> flags) {
  REPORT_AND_RETURN_IF_NULL_HANDLE(LibvirtStorageVolume(LibvirtStoragePoolCreationKey{}, nullptr));
  if(!volume) {
    report_error(datatype::ErrorCode::NULL_DOMAIN_PTR , ErrMsg::null_domain_ptr);
    return LibvirtStorageVolume(LibvirtStoragePoolCreationKey{}, nullptr);
  }
  virStorageVolPtr vol =  virStorageVolCreateXMLFrom(get_handle(), xml_config.c_str(), volume.get_handle(), std::accumulate(flags.begin(), flags.end(), 0, std::bit_or<std::uint64_t>()));
  if(!vol) report_error(datatype::ErrorCode::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error);
  return LibvirtStorageVolume(LibvirtStoragePoolCreationKey{}, vol);
}
