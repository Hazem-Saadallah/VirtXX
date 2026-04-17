#pragma once

#include <cstdint>
#include <variant>
#include <unordered_map>
#include <VirtXX/Impl/Misc.hxx>
#include <VirtXX/Impl/Config/Datatype.hxx>
#include <VirtXX/Impl/Config/ConfigValue.hxx>
#include <VirtXX/Impl/Config/Base/BaseConfig.hxx>

namespace Config {
  namespace Impl{
    class StorageVolumeConfig : Config::BaseConfig {
    public:
      enum class Field : std::uint8_t { TYPE, NAME, CAPACITY, CAPACITY_UNIT, ALLOCATION, ALLOCATION_UNIT, TARGET_FORMAT_TYPE, };

    private:
      std::unordered_map<Config::Impl::StorageVolumeConfig::Field, std::variant<ConfigValue<std::string>, ConfigValue<std::uint64_t>>> m_Values = {
        {Config::Impl::StorageVolumeConfig::Field::TYPE, ConfigValue<std::string>({""}, Config::Impl::Datatype::get_storage_volume_type_string(Config::Impl::Datatype::StorageVolumeType::FILE))},
        {Config::Impl::StorageVolumeConfig::Field::NAME, ConfigValue<std::string>({""}, Misc::generate_random_string(10, "VirtXX_VOLUME_", ""))},
        {Config::Impl::StorageVolumeConfig::Field::CAPACITY, ConfigValue<std::uint64_t>({""}, 0)},
        {Config::Impl::StorageVolumeConfig::Field::CAPACITY_UNIT, ConfigValue<std::string>({""}, Config::Impl::Datatype::get_storage_unit_string(Config::Impl::Datatype::StorageUnit::BYTES))},
        {Config::Impl::StorageVolumeConfig::Field::ALLOCATION, ConfigValue<std::uint64_t>({""}, 0)},
        {Config::Impl::StorageVolumeConfig::Field::ALLOCATION_UNIT, ConfigValue<std::string>({""}, Config::Impl::Datatype::get_storage_unit_string(Config::Impl::Datatype::StorageUnit::BYTES))},
        {Config::Impl::StorageVolumeConfig::Field::TARGET_FORMAT_TYPE, ConfigValue<std::string>({""}, Config::Impl::Datatype::get_file_format_type_string(Config::Impl::Datatype::FileFormatType::RAW))},
      };

    public:
      StorageVolumeConfig();
      ~StorageVolumeConfig() = default;
      StorageVolumeConfig(StorageVolumeConfig&& other) noexcept = default;
      StorageVolumeConfig &operator=(StorageVolumeConfig&& other) noexcept = default;
      StorageVolumeConfig(const StorageVolumeConfig& other) = delete;
      StorageVolumeConfig &operator=(const StorageVolumeConfig& other) = delete;

    public:
      std::string get_type();
      void set_type(Config::Impl::Datatype::StorageVolumeType type);

      std::string get_name();
      void set_name(const std::string& name);

      std::uint64_t get_capacity();
      void set_capacity(std::uint64_t capacity);

      std::string get_capacity_unit();
      void set_capacity_unit(Config::Impl::Datatype::StorageUnit unit);

      std::uint64_t get_allocation();
      void set_allocation(std::uint64_t allocation);

      std::string get_allocation_unit();
      void set_allocation_unit(Config::Impl::Datatype::StorageUnit unit);

      std::string get_file_format_type();
      void set_file_format_type(Config::Impl::Datatype::FileFormatType format_type);
    };
  }
}
