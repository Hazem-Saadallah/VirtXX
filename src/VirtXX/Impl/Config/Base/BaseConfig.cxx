#include <memory>
#include <sstream>
#include <string>
#include <optional>
#include <pugixml.hpp>
#include <VirtXX/Impl/Config/Base/BaseConfig.hxx>
#include <VirtXX/Impl/Config/Datatype.hxx>
#include <VirtXX/Impl/Config/Value.hxx>
#include <variant>


VirtXX::Impl::Config::BaseConfig::BaseConfig() : m_Document(std::make_shared<VirtXX::Impl::Config::Document>()) { }

std::optional<std::string> VirtXX::Impl::Config::BaseConfig::get_xml_string() const {
  std::stringstream ss;
  m_Document->get_internal_document()->save(ss);
  return ss.str();
}

void VirtXX::Impl::Config::BaseConfig::save_to_file(const std::string& file_path) { m_Document->get_internal_document()->save_file(file_path.c_str()); }

void VirtXX::Impl::Config::BaseConfig::compile_config() {
  for(VirtXX::Impl::Config::Datatype::ConfigValueMap::iterator itr=m_Values.begin(); itr != m_Values.end(); ++itr)
    std::visit([](auto& val){ val.set_or_create_value_or_default(); }, itr->second);
}

void VirtXX::Impl::Config::BaseConfig::set_value_map(Datatype::ConfigValueMap&& value_map) { m_Values = std::move(value_map); }

pugi::xml_parse_result VirtXX::Impl::Config::BaseConfig::load_file(const std::string file_path) {
  return m_Document->get_internal_document()->load_file(file_path.c_str());
}

pugi::xml_parse_result VirtXX::Impl::Config::BaseConfig::load_string(const std::string xml_string) {
  return m_Document->get_internal_document()->load_string(xml_string.c_str());
}

VirtXX::Impl::Config::Datatype::ConfigValueMap VirtXX::Impl::Config::BaseConfig::get_value_map() { return m_Values; }
VirtXX::Impl::Config::Datatype::SharedDocument VirtXX::Impl::Config::BaseConfig::get_document() { return m_Document; }
