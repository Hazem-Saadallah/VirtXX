#pragma once

#include "VirtXX/Impl/Config/StoragePoolConfig.hxx"
#include <cmath>
#include <vector>
#include <libvirt/libvirt.h>
#include <VirtXX/Impl/ErrorBlock.hxx>
#include <VirtXX/Impl/LibvirtStorageVolume.hxx>
#include <VirtXX/Impl/LibvirtConnectionCreationKey.hxx>

namespace VirtXX {
namespace Impl {
class LibvirtStoragePool {
public:
  // enum class SizeType : std::uint8_t { BYTE=0, KIB, MIB, GIB, TIB };

private:
  datatype::LibvirtInternalStoragePoolPtr m_Handle;
  mutable ErrorBlock m_LastError;

  void report_error(datatype::ErrorCode code, datatype::ErrorMsg msg) const;

public:
  LibvirtStoragePool() = default;
  LibvirtStoragePool(LibvirtConnectionCreationKey, virStoragePoolPtr storage_pool_ptr);
  ~LibvirtStoragePool();
  LibvirtStoragePool(LibvirtStoragePool &&) noexcept = default;
  LibvirtStoragePool &operator=(LibvirtStoragePool &&) noexcept = default;
  LibvirtStoragePool(const LibvirtStoragePool &) = default;
  LibvirtStoragePool &operator=(const LibvirtStoragePool &) = default;

  explicit operator bool() const;

  [[nodiscard]] bool is_active();
  void activate(std::vector<virStoragePoolCreateFlags> flags={});
  void destroy();
  void deactivate();
  void set_activation(bool active);
  [[nodiscard]] bool is_auto_start();
  void set_auto_start(bool auto_start);
  [[nodiscard]] bool is_persistent();
  void make_persistent(std::vector<virStoragePoolBuildFlags> flags);
  void undefine();
  void refresh();

  [[nodiscard]] virStoragePoolPtr get_handle() const;

  [[nodiscard]] std::string get_name() const;
  [[nodiscard]] std::string get_uuid_string() const;
  [[nodiscard]] datatype::UUIDBytes get_uuid() const;
  [[nodiscard]] VirtXX::Impl::Config::StoragePoolConfig get_xml_config(std::vector<virStorageXMLFlags> flags={}) const;

  [[nodiscard]] virStoragePoolInfo get_info() const;
  [[nodiscard]] virStoragePoolState get_state() const;
  [[nodiscard]] std::string  get_state_string() const;
  [[nodiscard]] std::double_t get_capacity(datatype::SizeType size_type=datatype::SizeType::MIB) const;
  [[nodiscard]] std::double_t get_allocated_space(datatype::SizeType size_type=datatype::SizeType::MIB) const;
  [[nodiscard]] std::double_t get_available_space(datatype::SizeType size_type=datatype::SizeType::MIB) const;

  [[nodiscard]] std::int32_t get_num_of_volumes() const;
  [[nodiscard]] LibvirtStorageVolume get_volume_by_name(std::string name) const;
  [[nodiscard]] datatype::StorageVolumeList get_volumes() const;

  [[nodiscard]] LibvirtStorageVolume create_storage_volume(const std::string& xml_config, std::vector<virStorageVolCreateFlags> flags={});
  [[nodiscard]] LibvirtStorageVolume clone_storage_volume(LibvirtStorageVolume volume, const std::string& xml_config, std::vector<virStorageVolCreateFlags> flags={});
}; /* LibvirtStoragePool */
} /* Impl */
} /* VirtXX */
