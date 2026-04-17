#include "VirtXX/Impl/Config/Datatype.hxx"
#include <VirtXX/Impl/Config/StorageVolumeConfig.hxx>

Config::Impl::StorageVolumeConfig::StorageVolumeConfig() : Config::BaseConfig() {
  pugi::xml_parse_result result = m_Document.load_string(R"(
    <?xml version="1.0" encoding="UTF-8"?>
    <volume type=''>
      <name></name>
      <capacity unit=""></capacity>
      <allocation unit=""></allocation>
      <target>
        <format type=''/>
      </target>
    </volume>
  )");

  if(!result) { /* TODO: Add error handling */ }
}


std::string Config::Impl::StorageVolumeConfig::get_type() { return std::get<ConfigValue<std::string>>(m_Values.at(Field::TYPE)).get_value_or_default(); }
void Config::Impl::StorageVolumeConfig::set_type(Config::Impl::Datatype::StorageVolumeType type) { std::get<ConfigValue<std::string>>((m_Values.at(Field::TYPE))).set_value(Config::Impl::Datatype::get_storage_volume_type_string(type)); }

std::string Config::Impl::StorageVolumeConfig::get_name() { return std::get<ConfigValue<std::string>>(m_Values.at(Field::NAME)).get_value_or_default(); }
void Config::Impl::StorageVolumeConfig::set_name(const std::string& name) { std::get<ConfigValue<std::string>>((m_Values.at(Field::NAME))).set_value(name); }

std::uint64_t Config::Impl::StorageVolumeConfig::get_capacity() { return std::get<ConfigValue<std::uint64_t>>(m_Values.at(Field::CAPACITY)).get_value_or_default(); }
void Config::Impl::StorageVolumeConfig::set_capacity(std::uint64_t capacity) { std::get<ConfigValue<std::uint64_t>>((m_Values.at(Field::CAPACITY))).set_value(capacity); }

std::string Config::Impl::StorageVolumeConfig::get_capacity_unit() { return std::get<ConfigValue<std::string>>(m_Values.at(Field::CAPACITY_UNIT)).get_value_or_default(); }
void Config::Impl::StorageVolumeConfig::set_capacity_unit(Config::Impl::Datatype::StorageUnit unit) { std::get<ConfigValue<std::string>>((m_Values.at(Field::CAPACITY_UNIT))).set_value(Config::Impl::Datatype::get_storage_unit_string(unit)); }

std::uint64_t Config::Impl::StorageVolumeConfig::get_allocation() { return std::get<ConfigValue<std::uint64_t>>(m_Values.at(Field::ALLOCATION)).get_value_or_default(); }
void Config::Impl::StorageVolumeConfig::set_allocation(std::uint64_t allocation) { std::get<ConfigValue<std::uint64_t>>((m_Values.at(Field::ALLOCATION))).set_value(allocation); }

std::string Config::Impl::StorageVolumeConfig::get_allocation_unit() { return std::get<ConfigValue<std::string>>(m_Values.at(Field::ALLOCATION)).get_value_or_default(); }
void Config::Impl::StorageVolumeConfig::set_allocation_unit(Config::Impl::Datatype::StorageUnit unit) { std::get<ConfigValue<std::string>>((m_Values.at(Field::ALLOCATION_UNIT))).set_value(Config::Impl::Datatype::get_storage_unit_string(unit)); }

std::string Config::Impl::StorageVolumeConfig::get_file_format_type() { return std::get<ConfigValue<std::string>>(m_Values.at(Field::TARGET_FORMAT_TYPE)).get_value_or_default(); }
void Config::Impl::StorageVolumeConfig::set_file_format_type(Config::Impl::Datatype::FileFormatType format_type) {
  std::get<ConfigValue<std::string>>((m_Values.at(Field::TARGET_FORMAT_TYPE))).set_value(Config::Impl::Datatype::get_file_format_type_string(format_type));
}
