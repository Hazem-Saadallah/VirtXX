#pragma once

#include <cmath>
#include <cstddef>
#include <vector>
#include <libvirt/libvirt.h>
#include <ErrorBlock.hxx>
#include <LibvirtStorageVolume.hxx>
#include <LibvirtConnectionCreationKey.hxx>

class _LibvirtStoragePool {
public:
  enum class SizeType : std::uint8_t {
    BYTE=0,
    KIB,
    MIB,
    GIB,
    TIB
  };

private:
  _datatype::_LibvirtInternalStoragePoolPtr m_Handle;
  _ErrorBlock m_LastError;

  void report_error(_datatype::ErrorCode_t code, _datatype::ErrorMsg_t msg);

public:
  _LibvirtStoragePool() = default;
  _LibvirtStoragePool(_LibvirtConnectionCreationKey, virStoragePoolPtr storage_pool_ptr);
  ~_LibvirtStoragePool();
  _LibvirtStoragePool(_LibvirtStoragePool &&) noexcept = default;
  _LibvirtStoragePool &operator=(_LibvirtStoragePool &&) noexcept = default;
  _LibvirtStoragePool(const _LibvirtStoragePool &) = default;
  _LibvirtStoragePool &operator=(const _LibvirtStoragePool &) = default;

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

  [[nodiscard]] std::string get_name();
  [[nodiscard]] std::string get_uuid_string();
  [[nodiscard]] _datatype::_UUIDBytes get_uuid();
  [[nodiscard]] std::string get_xml_config(std::vector<virStorageXMLFlags> flags={});

  [[nodiscard]] virStoragePoolInfo get_info();
  [[nodiscard]] virStoragePoolState get_state();
  [[nodiscard]] std::double_t get_capacity(SizeType size_type=SizeType::MIB);
  [[nodiscard]] std::double_t get_allocated_space(SizeType size_type=SizeType::MIB);
  [[nodiscard]] std::double_t get_available_space(SizeType size_type=SizeType::MIB);

  [[nodiscard]] std::int32_t get_num_of_volumes();
  [[nodiscard]] _LibvirtStorageVolume get_volume_by_name(std::string name);
  [[nodiscard]] _datatype::_StorageVolumeList get_volumes();

  [[nodiscard]] _LibvirtStorageVolume create_storage_volume(const std::string& xml_config, std::vector<virStorageVolCreateFlags> flags={});
  [[nodiscard]] _LibvirtStorageVolume clone_storage_volume(_LibvirtStorageVolume volume, const std::string& xml_config, std::vector<virStorageVolCreateFlags> flags={});
};
