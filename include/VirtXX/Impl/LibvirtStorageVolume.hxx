#pragma once

#include "VirtXX/Impl/Config/StorageVolumeConfig.hxx"
#include <string>
#include <libvirt/libvirt.h>
#include <VirtXX/Impl/datatypes.hxx>
#include <VirtXX/Impl/ErrorBlock.hxx>
#include <VirtXX/Impl/LibvirtConnectionCreationKey.hxx>
#include <VirtXX/Impl/LibvirtStoragePoolCreationKey.hxx>
#include <vector>

namespace VirtXX {
  namespace Impl {
    class LibvirtStorageVolume {
    friend LibvirtStoragePool;

    private:
      datatype::LibvirtInternalStorageVolumePtr m_Handle;
      ErrorBlock m_LastError;

      virStorageVolPtr get_handle() const;
      void report_error(datatype::ErrorCode code, datatype::ErrorMsg);

    public:
      LibvirtStorageVolume(LibvirtConnectionCreationKey, virStorageVolPtr storage_volume_ptr);
      LibvirtStorageVolume(LibvirtStoragePoolCreationKey, virStorageVolPtr storage_volume_ptr);
      ~LibvirtStorageVolume();
      LibvirtStorageVolume(LibvirtStorageVolume &&) noexcept = default;
      LibvirtStorageVolume &operator=(LibvirtStorageVolume &&) noexcept = default;
      LibvirtStorageVolume(const LibvirtStorageVolume &) = default;
      LibvirtStorageVolume &operator=(const LibvirtStorageVolume &) = default;

      explicit operator bool() const;

      [[nodiscard]] std::string get_key();
      [[nodiscard]] std::string get_name();
      [[nodiscard]] std::string get_path();
      [[nodiscard]] virStorageVolInfo get_info(std::vector<virStorageVolInfoFlags> flags={});
      [[nodiscard]] virStorageVolType get_type();
      [[nodiscard]] std::uint64_t get_capacity();
      [[nodiscard]] std::uint64_t get_allocation();
      [[nodiscard]] VirtXX::Impl::Config::StorageVolumeConfig get_xml_config();
    };
  }
}
