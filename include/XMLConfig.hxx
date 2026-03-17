#pragma once

#include <string> 

namespace _XMLConfig {
  std::string BasicStoragePool(std::string name, std::string target_path, std::string type="dir");
  std::string BasicStorageVolume(std::string name, std::string capacity_unit, std::string capacity, std::string allocation, std::string target_format_type="qcow2", std::string type="file");
}
