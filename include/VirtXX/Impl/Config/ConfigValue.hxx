#pragma once

#include <vector>
#include <string>
#include <optional>

namespace VirtXX {
  namespace Config {
    namespace Impl {
      template <typename T> class ConfigValue {
      private:
        std::optional<T> m_Value;
        const std::vector<std::string> m_XPath;
        const T m_Default;

      public:
        constexpr ConfigValue(std::vector<std::string> path, T default_value, std::optional<T> value=std::nullopt) : m_Value(value), m_XPath(path), m_Default(default_value) { }
        constexpr ~ConfigValue() = default;
        constexpr ConfigValue(ConfigValue&& other) noexcept = default;
        constexpr ConfigValue &operator=(ConfigValue&& other) noexcept = default;
        constexpr ConfigValue(const ConfigValue& other) = default;
        constexpr ConfigValue &operator=(const ConfigValue& other) = default;

      public:
        constexpr void set_value(T value) { m_Value = value; }
        constexpr bool has_value() { return m_Value.has_value(); }
        constexpr T get_value() { return m_Value.value(); }
        constexpr std::optional<T> get_value_opt() { return m_Value; }
        constexpr T get_default_value() const { return m_Default; }
        constexpr T get_value_or_default() const { return m_Value.value_or(m_Default); }
        constexpr std::vector<std::string> get_path() const { return m_XPath; }
      };
    }
  }
}
