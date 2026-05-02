#pragma once

#include <vector>
#include <string>
#include <optional>
#include <VirtXX/Impl/Config/Base/BaseConfig.hxx>

namespace VirtXX {
namespace Impl {
namespace Config {
  template <typename ValueType> class Value {
  private:
    Datatype::SharedDocument m_Document;
    std::vector<std::string> m_Path={};
    ValueType m_Default=ValueType();

  public:
    Value(Datatype::SharedDocument document, Datatype::PathType path, ValueType default_value) : m_Document(document), m_Path(path), m_Default(default_value) {}
    ~Value() = default;
    Value(Value&& other) noexcept = default;
    Value &operator=(Value&& other) noexcept = default;
    Value(const Value& other) = default;
    Value &operator=(const Value& other) = default;

  public:
    std::optional<ValueType> get_value() const { return m_Document->get_as<ValueType>(m_Path); }
    ValueType get_value_or_default() const { return m_Document->get_as<ValueType>(m_Path).value_or(m_Default); }
    void set_value(ValueType value) { m_Document->set_as<ValueType>(m_Path, value); }
    void set_or_create_value(ValueType value) { m_Document->set_or_create_as<ValueType>(m_Path, value); }

    void set_value_or_default() { m_Document->set_as<ValueType>(m_Path, get_value_or_default()); }
    void set_or_create_value_or_default() { m_Document->set_or_create_as<ValueType>(m_Path, get_value_or_default()); }

    ValueType get_default() const { return m_Default; };
    void set_default(ValueType value) { m_Default = value; }

    Datatype::PathType get_path() const { return m_Path; }
    void set_path(Datatype::PathType path) { m_Path = path; }

    Datatype::SharedDocument get_document() { return m_Document; }
    void set_config(Datatype::SharedDocument document) { m_Document = document; }
  };
}
}
}
