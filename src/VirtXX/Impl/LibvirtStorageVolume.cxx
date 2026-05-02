#include <numeric>
#include <functional>
#include <libvirt/libvirt.h>
#include <VirtXX/Impl/ErrMsg.hxx>
#include <VirtXX/Impl/LibvirtStorageVolume.hxx>
#include <VirtXX/Impl/Config/StorageVolumeConfig.hxx>

VirtXX::Impl::LibvirtStorageVolume::LibvirtStorageVolume(LibvirtConnectionCreationKey, virStorageVolPtr storage_volume_ptr)
: m_Handle(storage_volume_ptr, Deleters::LibvirtStorageVolumePtrDeleter()), m_LastError(datatype::ErrorCode::NONE, ErrMsg::not_an_error){}

VirtXX::Impl::LibvirtStorageVolume::LibvirtStorageVolume(LibvirtStoragePoolCreationKey, virStorageVolPtr storage_volume_ptr)
: m_Handle(storage_volume_ptr, Deleters::LibvirtStorageVolumePtrDeleter()), m_LastError(datatype::ErrorCode::NONE, ErrMsg::not_an_error){}

VirtXX::Impl::LibvirtStorageVolume::~LibvirtStorageVolume() = default;

VirtXX::Impl::LibvirtStorageVolume::operator bool() const { return m_Handle != nullptr; }

virStorageVolPtr VirtXX::Impl::LibvirtStorageVolume::get_handle() const { return m_Handle.get(); }

std::string VirtXX::Impl::LibvirtStorageVolume::get_key() { return virStorageVolGetKey(get_handle()); }
std::string VirtXX::Impl::LibvirtStorageVolume::get_name() { return virStorageVolGetName(get_handle()); }
std::string VirtXX::Impl::LibvirtStorageVolume::get_path() { return virStorageVolGetPath(get_handle()); }

virStorageVolInfo VirtXX::Impl::LibvirtStorageVolume::get_info(std::vector<virStorageVolInfoFlags> flags) {
  virStorageVolInfo info;
  virStorageVolGetInfoFlags(get_handle(), &info, std::accumulate(flags.begin(), flags.end(),
        static_cast<std::uint32_t>(VIR_STORAGE_VOL_USE_ALLOCATION), std::bit_or<std::uint32_t>()));
  return info;
}

virStorageVolType VirtXX::Impl::LibvirtStorageVolume::get_type() { return static_cast<virStorageVolType>(get_info().type); }
std::uint64_t VirtXX::Impl::LibvirtStorageVolume::get_capacity() { return get_info().capacity; }
std::uint64_t VirtXX::Impl::LibvirtStorageVolume::get_allocation() { return get_info().allocation; }

VirtXX::Impl::Config::StorageVolumeConfig VirtXX::Impl::LibvirtStorageVolume::get_xml_config() {
  char *buffer = virStorageVolGetXMLDesc(get_handle(), 0);
  if(!buffer) return VirtXX::Impl::Config::StorageVolumeConfig();
  VirtXX::Impl::Config::StorageVolumeConfig storage_volume_config;
  storage_volume_config.load_string(std::string(buffer));
  std::free(buffer);
  return storage_volume_config;
}
