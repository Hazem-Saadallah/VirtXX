#include <sstream>
#include <string>
#include <optional>
#include <pugixml.hpp>
#include <VirtXX/Impl/Config/Base/BaseConfig.hxx>

std::optional<std::string> VirtXX::Config::Impl::BaseConfig::get_xml() const {
  std::stringstream ss;
  m_Document.save(ss);
  return ss.str();
}

void VirtXX::Config::Impl::BaseConfig::save_to_file(const std::string& file_path) {
  m_Document.save_file(file_path.c_str());
}

std::optional<pugi::xml_node> VirtXX::Config::Impl::BaseConfig::navigate_parents(std::span<const std::string> path, bool create_missing) const {
  if (path.empty()) return std::nullopt;
  pugi::xml_node current = m_Document;
  for (size_t i = 0; i < path.size(); ++i) {
    pugi::xml_node next = current.child(path[i].c_str());
      if (!next) {
        if (create_missing) next = current.append_child(path[i].c_str());
        else return std::nullopt;
      }
      current = next;
    }
  return current;
}

