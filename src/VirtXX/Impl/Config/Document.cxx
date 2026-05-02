#include <VirtXX/Impl/Config/Document.hpp>
#include <memory>


VirtXX::Impl::Config::Document::Document() : m_Document(std::make_shared<pugi::xml_document>()) {}

std::optional<pugi::xml_node> VirtXX::Impl::Config::Document::navigate_parents(std::span<const std::string> path, bool create_missing) const {
  if (path.empty()) return std::nullopt;
  pugi::xml_node current = *m_Document;
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

VirtXX::Impl::Config::Datatype::SharedInternalocument VirtXX::Impl::Config::Document::get_internal_document() const {
  std::shared_lock<std::shared_mutex> lock(m_RWMutex);
  return m_Document;
}
