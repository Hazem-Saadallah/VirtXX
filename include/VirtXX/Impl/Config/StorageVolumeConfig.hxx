#pragma once

#include <cstdint>
#include <VirtXX/Impl/Misc.hxx>
#include <VirtXX/Impl/Config/Datatype.hxx>
#include <VirtXX/Impl/Config/Value.hxx>
#include <VirtXX/Impl/Config/Base/BaseConfig.hxx>

namespace VirtXX {
namespace Impl{
namespace Config {
  class StorageVolumeConfig : public BaseConfig {
  public:
    enum class Field : std::uint8_t { TYPE, NAME, CAPACITY, CAPACITY_UNIT, ALLOCATION, ALLOCATION_UNIT, TARGET_FORMAT_TYPE, };

  public:
    StorageVolumeConfig();
    ~StorageVolumeConfig() = default;
    StorageVolumeConfig(StorageVolumeConfig&& other) noexcept = default;
    StorageVolumeConfig &operator=(StorageVolumeConfig&& other) noexcept = default;
    StorageVolumeConfig(const StorageVolumeConfig& other) = default;
    StorageVolumeConfig &operator=(const StorageVolumeConfig& other) = default;

  public:
    std::string get_type();
    void set_type(Datatype::StorageVolumeType type);

    std::string get_name();
    void set_name(const std::string& name);

    std::uint64_t get_capacity();
    void set_capacity(std::uint64_t capacity);

    std::string get_capacity_unit();
    void set_capacity_unit(Datatype::StorageUnit unit);

    std::uint64_t get_allocation();
    void set_allocation(std::uint64_t allocation);

    std::string get_allocation_unit();
    void set_allocation_unit(Datatype::StorageUnit unit);

    std::string get_file_format_type();
    void set_file_format_type(Datatype::FileFormatType format_type);
  };
} /* Config */
} /* Impl   */
} /* VirtXX */
