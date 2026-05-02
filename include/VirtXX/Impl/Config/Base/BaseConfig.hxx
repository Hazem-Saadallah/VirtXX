#pragma once

#include <string>
#include <optional>
#include <pugixml.hpp>
#include <VirtXX/Impl/Config/Datatype.hxx>
#include <VirtXX/Impl/Config/Document.hpp>


namespace VirtXX {
namespace Impl {
namespace Config {
  template<typename ValueType> class Value;

  class BaseConfig {
  public:

  protected:
    Datatype::SharedDocument m_Document;
    Datatype::ConfigValueMap m_Values;

  protected:
    BaseConfig();
    ~BaseConfig() = default;
    BaseConfig(BaseConfig&& other) noexcept = default;
    BaseConfig &operator=(BaseConfig&& other) noexcept = default;
    BaseConfig(const BaseConfig& other) = default;
    BaseConfig &operator=(const BaseConfig& other) = default;

  public:
    void compile_config();
    std::optional<std::string> get_xml_string() const;
    void save_to_file(const std::string& file_path);
    template<typename ValueType> void set_field_value(std::uint8_t field_id, ValueType value) { std::get<Value<ValueType>>(m_Values.at(field_id)).set_value(value); }
    template<typename ValueType> void set_or_create_field_value(std::uint8_t field_id, ValueType value) { std::get<Value<ValueType>>(m_Values.at(field_id)).set_or_create_value(value); }
    template<typename ValueType> ValueType get_field_value(std::uint8_t field_id) { return std::get<Value<ValueType>>(m_Values.at(field_id)).get_value().value(); }
    template<typename ValueType> ValueType get_field_value_or_default(std::uint8_t field_id) { return std::get<Value<ValueType>>(m_Values.at(field_id)).get_value_or_default(); }

    pugi::xml_parse_result load_file(const std::string file_path);
    pugi::xml_parse_result load_string(const std::string xml_string);

    Datatype::ConfigValueMap get_value_map();
    Datatype::SharedDocument get_document();

  protected:
    void set_value_map(Datatype::ConfigValueMap&& value_map);
  };
} /* Config */
} /* Impl   */
} /* VirtXX */
