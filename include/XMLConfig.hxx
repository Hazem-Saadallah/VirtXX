#pragma once

#include <string> 

class XMLConfig {
private:
  XMLConfig() = delete;
  XMLConfig(XMLConfig &&) = delete;
  XMLConfig(const XMLConfig &) = delete;
  XMLConfig &operator=(XMLConfig &&) = delete;
  XMLConfig &operator=(const XMLConfig &) = delete;
  ~XMLConfig() = delete;

public:
  static std::string BasicStoragePool(std::string name, std::string target_path, std::string type="dir");
  static std::string BasicStorageVolume(std::string name, std::string capacity_unit, std::string capacity, std::string allocation, std::string target_format_type="qcow2", std::string type="file");
};
