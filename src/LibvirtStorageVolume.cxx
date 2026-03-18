#include <libvirt/libvirt.h>
#include <ErrMsg.hxx>
#include <LibvirtStorageVolume.hxx>

_LibvirtStorageVolume::_LibvirtStorageVolume(_LibvirtConnectionCreationKey, virStorageVolPtr storage_volume_ptr)
: m_Handle(storage_volume_ptr, Deleters::_LibvirtStorageVolumePtrDeleter()), m_LastError(_datatype::ErrorCode_t::NONE, ErrMsg::not_an_error){}

_LibvirtStorageVolume::_LibvirtStorageVolume(_LibvirtStoragePoolCreationKey, virStorageVolPtr storage_volume_ptr)
: m_Handle(storage_volume_ptr, Deleters::_LibvirtStorageVolumePtrDeleter()), m_LastError(_datatype::ErrorCode_t::NONE, ErrMsg::not_an_error){}

_LibvirtStorageVolume::~_LibvirtStorageVolume() = default;

_LibvirtStorageVolume::operator bool() const { return m_Handle != nullptr; }

virStorageVolPtr _LibvirtStorageVolume::get_handle() const { return m_Handle.get(); }

std::string _LibvirtStorageVolume::get_key() {
  return virStorageVolGetKey(get_handle());
}

std::string _LibvirtStorageVolume::get_name() {
  return virStorageVolGetName(get_handle());
}

std::string _LibvirtStorageVolume::get_path() {
  return virStorageVolGetPath(get_handle());
}

std::string _LibvirtStorageVolume::get_xml_config() {
  char *buffer = virStorageVolGetXMLDesc(get_handle(), 0);
  if(!buffer) return std::string();
  std::string data = std::string(buffer);
  std::free(buffer);
  return data;
}
