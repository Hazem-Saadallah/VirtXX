#include <string>
#include <pugixml.hpp>
#include <VirtXX/Impl/Config/StoragePoolConfig.hxx>

VirtXX::Config::Impl::StoragePoolConfig::StoragePoolConfig() : VirtXX::Config::Impl::BaseConfig() {
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

std::string VirtXX::Config::Impl::StoragePoolConfig::get_type() { return std::get<ConfigValue<std::string>>(m_Values.at(Field::TYPE)).get_value_or_default(); }
void VirtXX::Config::Impl::StoragePoolConfig::set_type(Datatype::StoragePoolType type) {
  std::get<ConfigValue<std::string>>(m_Values.at(Field::TYPE)).set_value(Datatype::get_storage_pool_type_string(type));
}

std::string VirtXX::Config::Impl::StoragePoolConfig::get_name() { return std::get<ConfigValue<std::string>>(m_Values.at(Field::NAME)).get_value_or_default(); }
void VirtXX::Config::Impl::StoragePoolConfig::set_name(const std::string& name) { std::get<ConfigValue<std::string>>(m_Values.at(Field::NAME)).set_value(name); }

std::string VirtXX::Config::Impl::StoragePoolConfig::get_target_path() { return std::get<ConfigValue<std::string>>(m_Values.at(Field::TARGET_PATH)).get_value_or_default(); }
void VirtXX::Config::Impl::StoragePoolConfig::set_target_path(const std::string& target_path) { std::get<ConfigValue<std::string>>(m_Values.at(Field::TARGET_PATH)).set_value(target_path); }
