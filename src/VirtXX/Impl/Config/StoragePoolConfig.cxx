#include <string>
#include <optional>
#include <pugixml.hpp>
#include <VirtXX/Impl/Config/StoragePoolConfig.hxx>

Config::StoragePoolConfig::StoragePoolConfig() : Config::BaseConfig() {
  pugi::xml_parse_result result = m_Document.load_string(R"(
    <?xml version="1.0" encoding="UTF-8"?>
    <pool type=''>
      <name></name>
      <target>
        <path></path>
      </target>
    </pool>
  )");

  if(!result) { /* TODO: Add error handling */ }
}

std::string Config::StoragePoolConfig::get_type() { return std::get<ConfigValue<std::string>>(m_Values.at(Config::StoragePoolConfig::Field::TYPE)).get_value_or_default(); }
void Config::StoragePoolConfig::set_type(Config::Impl::Datatype::StoragePoolType type) {
  std::get<ConfigValue<std::string>>(m_Values.at(Config::StoragePoolConfig::Field::TYPE)).set_value(Config::Impl::Datatype::get_storage_pool_type_string(type));
}

std::string Config::StoragePoolConfig::get_name() { return std::get<ConfigValue<std::string>>(m_Values.at(Config::StoragePoolConfig::Field::NAME)).get_value_or_default(); }
void Config::StoragePoolConfig::set_name(const std::string& name) { std::get<ConfigValue<std::string>>(m_Values.at(Config::StoragePoolConfig::Field::NAME)).set_value(name); }

std::string Config::StoragePoolConfig::get_target_path() { return std::get<ConfigValue<std::string>>(m_Values.at(Config::StoragePoolConfig::Field::TARGET_PATH)).get_value_or_default(); }
void Config::StoragePoolConfig::set_target_path(const std::string& target_path) { std::get<ConfigValue<std::string>>(m_Values.at(Config::StoragePoolConfig::Field::TARGET_PATH)).set_value(target_path); }
