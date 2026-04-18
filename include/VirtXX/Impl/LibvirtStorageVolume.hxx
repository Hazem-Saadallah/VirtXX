#pragma once

#include <string>
#include <libvirt/libvirt.h>
#include <VirtXX/Impl/datatypes.hxx>
#include <VirtXX/Impl/ErrorBlock.hxx>
#include <VirtXX/Impl/LibvirtConnectionCreationKey.hxx>
#include <VirtXX/Impl/LibvirtStoragePoolCreationKey.hxx>
#include <vector>

class _LibvirtStorageVolume {
friend _LibvirtStoragePool;

private:
  _datatype::_LibvirtInternalStorageVolumePtr m_Handle;
  _ErrorBlock m_LastError;

  virStorageVolPtr get_handle() const;
  void report_error(_datatype::ErrorCode_t code, _datatype::ErrorMsg_t);

public:
  _LibvirtStorageVolume(_LibvirtConnectionCreationKey, virStorageVolPtr storage_volume_ptr);
  _LibvirtStorageVolume(_LibvirtStoragePoolCreationKey, virStorageVolPtr storage_volume_ptr);
  ~_LibvirtStorageVolume();
  _LibvirtStorageVolume(_LibvirtStorageVolume &&) noexcept = default;
  _LibvirtStorageVolume &operator=(_LibvirtStorageVolume &&) noexcept = default;
  _LibvirtStorageVolume(const _LibvirtStorageVolume &) = default;
  _LibvirtStorageVolume &operator=(const _LibvirtStorageVolume &) = default;

  explicit operator bool() const;

  [[nodiscard]] std::string get_key();
  [[nodiscard]] std::string get_name();
  [[nodiscard]] std::string get_path();
  [[nodiscard]] virStorageVolInfo get_info(std::vector<virStorageVolInfoFlags> flags={});
  [[nodiscard]] virStorageVolType get_type();
  [[nodiscard]] std::uint64_t get_capacity();
  [[nodiscard]] std::uint64_t get_allocation();
  [[nodiscard]] std::string get_xml_config();
};
