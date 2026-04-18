#pragma once

#include <span>
#include <vector>
#include <string>
#include <optional>
#include <pugixml.hpp>

namespace VirtXX {
  namespace Config {
    namespace Impl {
      template <typename U> concept XmlValueSource = std::same_as<U, pugi::xml_attribute> || std::same_as<U, pugi::xml_text>;

      class BaseConfig {
      protected:
        pugi::xml_document m_Document;

      protected:
        BaseConfig() = default;
        ~BaseConfig() = default;
        BaseConfig(BaseConfig&& other) noexcept = default;
        BaseConfig &operator=(BaseConfig&& other) noexcept = default;
        BaseConfig(const BaseConfig& other) = delete;
        BaseConfig &operator=(const BaseConfig& other) = delete;

      public:
        std::optional<std::string> get_xml() const;
        void save_to_file(const std::string& file_path);

      protected:
        std::optional<pugi::xml_node> navigate_parents(std::span<const std::string> path, bool create_missing=false) const;

        template<typename T, XmlValueSource SourceType> std::optional<T> extract_value(SourceType source) const {
          if constexpr (std::is_same_v<T, std::string>) return std::string(source.as_string());
          else if constexpr (std::is_same_v<T, bool>) return source.as_bool();
          else if constexpr (std::is_floating_point_v<T>) {
            if constexpr (sizeof(T) == 8) return static_cast<T>(source.as_double());
            else return static_cast<T>(source.as_float());
          }
          else if constexpr (std::is_integral_v<T>) {
            if constexpr (sizeof(T) == 8) {
              if constexpr (std::is_signed_v<T>) return static_cast<T>(source.as_llong());
              else return static_cast<T>(source.as_ullong());
            } else {
              if constexpr (std::is_signed_v<T>) return static_cast<T>(source.as_int());
              else return static_cast<T>(source.as_uint());
            }
          }
          else return std::nullopt;
        }

        template <typename T> std::optional<T> get_as(const std::vector<std::string>& full_path) const {
          if(full_path.empty()) return std::nullopt;
          return get_as<T>(std::vector<std::string>(full_path.begin(), full_path.end()-1), full_path.back());
        }

        template <typename T> std::optional<T> get_as(const std::vector<std::string>& path, const std::string& key) const {
          if(key.empty()) return std::nullopt;
          std::optional<pugi::xml_node> parent = navigate_parents(path, false);
          if(!parent) return std::nullopt;
          pugi::xpath_node target = parent->select_node(key.c_str());
          if(target.attribute()) return extract_value<T, pugi::xml_attribute>(target.attribute());
          else if (target.node()) return extract_value<T, pugi::xml_text>(target.node().text());
          return std::nullopt;
        }

        template<typename T> void set_as(const std::vector<std::string>& path, const std::string& key, const T& value) {
          if(key.empty()) return;

          std::optional<pugi::xml_node> node = navigate_parents(path, false);
          if(!node.has_value()) return;
          if(key[0] == '@') {
            std::string attribute_name = key.substr(1);
            pugi::xml_attribute attribute = node.value().attribute(attribute_name.c_str());
            if(attribute) {
              if constexpr (std::is_same_v<T, std::string>) attribute.set_value(value.c_str());
              else attribute.set_value(value);
            } else { /* TODO: Add error handling */ }
          } else {
            pugi::xml_node child = node.value().child(key.c_str());
            if(child) {
              if constexpr (std::is_same_v<T, std::string>) child.text().set(value.c_str());
              else child.text().set(value);
            } else { /* TODO: Add error handling */ }
          }
        }

        template<typename T> void set_or_create_as(const std::vector<std::string>& path, const std::string& key, const T& value) {
          if(key.empty()) return;

          std::optional<pugi::xml_node> node = navigate_parents(path, true);
          if(!node.has_value()) return;
          if(key[0] == '@') {
            std::string attribute_name = key.substr(1);
            pugi::xml_attribute attribute = node.value().attribute(attribute_name.c_str());
            if(!attribute) attribute = node.value().append_attribute(attribute_name.c_str());
            if constexpr (std::is_same_v<T, std::string>) attribute.set_value(value.c_str());
            else attribute.set_value(value);
          } else {
            pugi::xml_node child = node.value().child(key.c_str());
            if(!child) child = node.value().append_child(key.c_str());
            if constexpr (std::is_same_v<T, std::string>) child.text().set(value.c_str());
            else child.text().set(value);
          }
        }
      };
    }
  }
}
