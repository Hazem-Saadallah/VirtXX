#include <string>
#include <sstream>
#include <pugixml.hpp>
#include <XMLConfig.hxx>

const static std::string basic_storage_pool_xml = R"(
<?xml version="1.0" encoding="UTF-8"?>
<pool type=''>
  <name></name>
  <target>
    <path></path>
  </target>
</pool>
)";

const static std::string basic_storage_volume_xml = R"(
<?xml version="1.0" encoding="UTF-8"?>
<volume type=''>
  <name></name>
  <capacity unit=""></capacity>
  <allocation></allocation>
  <target>
    <format type=''/>
  </target>
</volume>
)";


std::string _XMLConfig::BasicStoragePool(std::string name, std::string target_path, std::string type) {
  pugi::xml_document document;
  // pugi::xml_parse_result result = document.load_string(basic_storage_pool.c_str());
  pugi::xml_parse_result result = document.load_string(basic_storage_pool_xml.c_str());
  /* NOTE: Add error handling */

  document.child("pool").attribute("type").set_value(type);
  document.child("pool").child("name").text().set(name);
  document.child("pool").child("target").child("path").text().set(target_path);

  std::ostringstream oss;
  document.save(oss);
  std::string str_val = oss.str();
  return str_val;
}

std::string _XMLConfig::BasicStorageVolume(std::string name, std::string capacity_unit, std::string capacity, std::string allocation, std::string target_format_type, std::string type) {
  pugi::xml_document document;
  // pugi::xml_parse_result result = document.load_string(basic_storage_volume.c_str());
  pugi::xml_parse_result result = document.load_file(basic_storage_volume_xml.c_str());
  /* NOTE: Add error handling */

  document.child("volume").attribute("type").set_value(type);
  document.child("volume").child("name").text().set(name);
  document.child("volume").child("capacity").attribute("unit").set_value(capacity_unit);
  document.child("volume").child("capacity").text().set(capacity);
  document.child("volume").child("allocation").text().set(allocation);
  document.child("volume").child("target").child("format").attribute("type").set_value(target_format_type);

  std::ostringstream oss;
  document.save(oss);
  std::string str_val = oss.str();
  return str_val;
}
