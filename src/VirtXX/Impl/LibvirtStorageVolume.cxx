#include <functional>
#include <libvirt/libvirt.h>
#include <VirtXX/Impl/ErrMsg.hxx>
#include <VirtXX/Impl/LibvirtStorageVolume.hxx>
#include <numeric>

VirtXX::Impl::_LibvirtStorageVolume::_LibvirtStorageVolume(_LibvirtConnectionCreationKey, virStorageVolPtr storage_volume_ptr)
: m_Handle(storage_volume_ptr, Deleters::_LibvirtStorageVolumePtrDeleter()), m_LastError(_datatype::ErrorCode_t::NONE, ErrMsg::not_an_error){}

VirtXX::Impl::_LibvirtStorageVolume::_LibvirtStorageVolume(_LibvirtStoragePoolCreationKey, virStorageVolPtr storage_volume_ptr)
: m_Handle(storage_volume_ptr, Deleters::_LibvirtStorageVolumePtrDeleter()), m_LastError(_datatype::ErrorCode_t::NONE, ErrMsg::not_an_error){}

VirtXX::Impl::_LibvirtStorageVolume::~_LibvirtStorageVolume() = default;

VirtXX::Impl::_LibvirtStorageVolume::operator bool() const { return m_Handle != nullptr; }

virStorageVolPtr VirtXX::Impl::_LibvirtStorageVolume::get_handle() const { return m_Handle.get(); }

std::string VirtXX::Impl::_LibvirtStorageVolume::get_key() { return virStorageVolGetKey(get_handle()); }
std::string VirtXX::Impl::_LibvirtStorageVolume::get_name() { return virStorageVolGetName(get_handle()); }
std::string VirtXX::Impl::_LibvirtStorageVolume::get_path() { return virStorageVolGetPath(get_handle()); }

virStorageVolInfo VirtXX::Impl::_LibvirtStorageVolume::get_info(std::vector<virStorageVolInfoFlags> flags) {
  virStorageVolInfo info;
  virStorageVolGetInfoFlags(get_handle(), &info, std::accumulate(flags.begin(), flags.end(),
        static_cast<std::uint32_t>(VIR_STORAGE_VOL_USE_ALLOCATION), std::bit_or<std::uint32_t>()));
  return info;
}

virStorageVolType VirtXX::Impl::_LibvirtStorageVolume::get_type() { return static_cast<virStorageVolType>(get_info().type); }
std::uint64_t VirtXX::Impl::_LibvirtStorageVolume::get_capacity() { return get_info().capacity; }
std::uint64_t VirtXX::Impl::_LibvirtStorageVolume::get_allocation() { return get_info().allocation; }

std::string VirtXX::Impl::_LibvirtStorageVolume::get_xml_config() {
  char *buffer = virStorageVolGetXMLDesc(get_handle(), 0);
  if(!buffer) return std::string();
  std::string data = std::string(buffer);
  std::free(buffer);
  return data;
}
