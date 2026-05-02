#pragma once

#include <cmath>
#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include <variant>
#include <unordered_map>
#include <pugixml.hpp>

namespace VirtXX {
namespace Impl {
namespace Config {

class BaseConfig;
class Document;

template<typename ValueType> class Value;

namespace Datatype {
  enum class StoragePoolType : std::uint8_t { DIRECTORY, FILESYSTEM, NETWORK_FILESYSTEM, LOGICAL_VOLUME_MANAGER, DISK, ISCSI, ISCSI_DIRECT, SCSI, MULTIPATH, CEPH, RBD, SHEEPDOG, GLUSTER, ZFS, VSTORAGE, };
  enum class StorageVolumeType : std::uint8_t { FILE, BLOCK, DIRECTORY, NETWORK, NETDIR, PLOOP, };
  enum class StorageUnit : std::uint8_t { BYTES, B, KIB, KB, K, MIB, MB, M, GIB, GB, G, TIB, TB, T, PIB, PB, P, EIB, EB, E, };
  enum class FileFormatType : std::uint8_t { RAW, QCOW2, QCOW, QED, VMDK, VPC, ISO, BOCHS, CLOOP, DMG, };
  enum class DomainType : std::uint8_t {KVM, QEMU, LXC, XEN, BHYVE, HVF, VBOX, VMWARE, VZ, UML, POWERVM, };

  std::string get_storage_pool_type_string(StoragePoolType type);
  std::string get_storage_volume_type_string(StorageVolumeType type);
  std::string get_storage_unit_string(StorageUnit unit);
  std::string get_file_format_type_string(FileFormatType format_type);
  std::string get_domain_type_string(DomainType domain_type);

  typedef std::vector<std::string> PathType;
  typedef std::shared_ptr<BaseConfig> Config;
  typedef std::shared_ptr<pugi::xml_document> SharedInternalocument ;
  typedef std::shared_ptr<Document> SharedDocument ;

  typedef Value<std::uint64_t> ValueUInt64;
  typedef Value<std::double_t> ValueFloat64;
  typedef Value<std::string> ValueString;
  typedef Value<bool> ValueBool;
  typedef std::variant<ValueUInt64, ValueFloat64, ValueString, ValueBool> ValueVariant;

  typedef std::unordered_map<std::uint8_t, ValueVariant> ConfigValueMap;
} /* Datatype */
} /* Config   */
} /* Impl     */
} /* VirtXX   */
