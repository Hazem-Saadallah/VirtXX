#pragma once

#include <span>
#include <mutex>
#include <optional>
#include <shared_mutex>
#include <pugixml.hpp>
#include <VirtXX/Impl/Config/Datatype.hxx>

namespace VirtXX {
namespace Impl {
namespace Config {

template <typename U> concept XmlValueSource = std::same_as<U, pugi::xml_attribute> || std::same_as<U, pugi::xml_text>;

class Document {
private:
  mutable std::shared_mutex m_RWMutex;
  Datatype::SharedInternalocument m_Document;

public:
  Document();
  Document(pugi::xml_document document);
  ~Document() = default;
  Document(Document&& other) noexcept = delete;
  Document &operator=(Document&& other) noexcept = delete;
  Document(const Document& other) = delete;
  Document &operator=(const Document& other) = delete;

private:
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

  template <typename T> std::optional<T> get_as_impl(const Datatype::PathType& full_path) const {
    Datatype::PathType path = Datatype::PathType(full_path.begin(), full_path.end()-1);
    std::string key = full_path.back();

    if(key.empty()) return std::nullopt;
    std::optional<pugi::xml_node> parent = navigate_parents(path, false);
    if(!parent) return std::nullopt;
    pugi::xpath_node target = parent->select_node(key.c_str());
    if(target.attribute()) return extract_value<T, pugi::xml_attribute>(target.attribute());
    else if (target.node()) return extract_value<T, pugi::xml_text>(target.node().text());
    return std::nullopt;
  }

  template<typename T> void set_as_impl(const std::vector<std::string>& full_path, const T& value) {
    if(full_path.empty()) return;

    Datatype::PathType path = Datatype::PathType(full_path.begin(), full_path.end()-1);
    std::string key = full_path.back();

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

  template<typename T> void set_or_create_as_impl(const Datatype::PathType& full_path, const T& value) {
    Datatype::PathType path = Datatype::PathType(full_path.begin(), full_path.end()-1);
    std::string key = full_path.back();

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

public:
  Datatype::SharedInternalocument get_internal_document() const;

  template <typename T> std::optional<T> get_as(const std::vector<std::string>& full_path) const {
    std::shared_lock<std::shared_mutex> lock(m_RWMutex);
    return get_as_impl<T>(full_path);
  }

  template <typename T> std::optional<T> get_as(const std::vector<std::string>& path, const std::string& key) const {
    std::shared_lock<std::shared_mutex> lock(m_RWMutex);
    Datatype::PathType full_path = path;
    full_path.push_back(key);
    return get_as_impl<T>(full_path);
  }

  template<typename T> void set_as(const Datatype::PathType& full_path, const T& value) {
    std::unique_lock<std::shared_mutex> lock(m_RWMutex);
    set_as_impl(full_path, value);
  }

  template<typename T> void set_as(const Datatype::PathType& path, const std::string& key, const T& value) {
    std::unique_lock<std::shared_mutex> lock(m_RWMutex);
    Datatype::PathType full_path = path;
    full_path.push_back(key);
    set_as_impl(full_path, value);
  }
  template<typename T> void set_or_create_as(const std::vector<std::string>& full_path, const T& value) {
    std::unique_lock<std::shared_mutex> lock(m_RWMutex);
    set_or_create_as_impl(full_path, value);
  }

  template<typename T> void set_or_create_as(const std::vector<std::string>& path, const std::string& key, const T& value) {
    std::unique_lock<std::shared_mutex> lock(m_RWMutex);
    Datatype::PathType full_path = path;
    full_path.push_back(key);
    set_or_create_as_impl(full_path, value);
  }
};
} /* Config */
} /* Impl   */
} /* VirtXX */
