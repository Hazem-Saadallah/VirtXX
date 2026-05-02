#include <string>
#include <filesystem>
#include <pugixml.hpp>
#include <VirtXX/Impl/Config/StoragePoolConfig.hxx>

VirtXX::Impl::Config::StoragePoolConfig::StoragePoolConfig() : BaseConfig() {
  set_value_map({
    {static_cast<std::uint8_t>(StoragePoolConfig::Field::NAME), Datatype::ValueString(m_Document, {"pool", "name"}, VirtXX::Impl::Misc::generate_random_string(10, "VirtXX_POOL_", ""))},
    {static_cast<std::uint8_t>(StoragePoolConfig::Field::TYPE), Datatype::ValueString(m_Document, {"pool", "@type"}, Datatype::get_storage_pool_type_string(Datatype::StoragePoolType::DIRECTORY))},
    {static_cast<std::uint8_t>(StoragePoolConfig::Field::TARGET_PATH), Datatype::ValueString(m_Document, {"pool", "target", "path"}, std::filesystem::current_path().string())},
  });
}

std::string VirtXX::Impl::Config::StoragePoolConfig::get_type() { return std::get<VirtXX::Impl::Config::Value<std::string>>(m_Values.at(static_cast<std::uint8_t>(Field::TYPE))).get_value_or_default(); }
void VirtXX::Impl::Config::StoragePoolConfig::set_type(Datatype::StoragePoolType type) {
  std::get<VirtXX::Impl::Config::Value<std::string>>(m_Values.at(static_cast<std::uint8_t>(Field::TYPE))).set_value(Datatype::get_storage_pool_type_string(type));
}

std::string VirtXX::Impl::Config::StoragePoolConfig::get_name() { return std::get<VirtXX::Impl::Config::Value<std::string>>(m_Values.at(static_cast<std::uint8_t>(Field::NAME))).get_value_or_default(); }
void VirtXX::Impl::Config::StoragePoolConfig::set_name(const std::string& name) { std::get<VirtXX::Impl::Config::Value<std::string>>(m_Values.at(static_cast<std::uint8_t>(Field::NAME))).set_value(name); }

std::string VirtXX::Impl::Config::StoragePoolConfig::get_target_path() { return std::get<VirtXX::Impl::Config::Value<std::string>>(m_Values.at(static_cast<std::uint8_t>(Field::TARGET_PATH))).get_value_or_default(); }
void VirtXX::Impl::Config::StoragePoolConfig::set_target_path(const std::string& target_path) { std::get<VirtXX::Impl::Config::Value<std::string>>(m_Values.at(static_cast<std::uint8_t>(Field::TARGET_PATH))).set_value(target_path); }
