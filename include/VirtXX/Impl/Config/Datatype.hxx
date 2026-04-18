#pragma once

#include <cstdint>
#include <string>

namespace VirtXX {
  namespace Config {
    namespace Impl {
      namespace Datatype {
        enum class StoragePoolType : std::uint8_t { DIRECTORY, FILESYSTEM, NETWORK_FILESYSTEM, LOGICAL_VOLUME_MANAGER, DISK, ISCSI, ISCSI_DIRECT, SCSI, MULTIPATH, CEPH, RBD, SHEEPDOG, GLUSTER, ZFS, VSTORAGE, };
        enum class StorageVolumeType : std::uint8_t { FILE, BLOCK, DIRECTORY, NETWORK, NETDIR, PLOOP, };
        enum class StorageUnit : std::uint8_t { BYTES, B, KIB, KB, K, MIB, MB, M, GIB, GB, G, TIB, TB, T, PIB, PB, P, EIB, EB, E, };
        enum class FileFormatType : std::uint8_t { RAW, QCOW2, QCOW, QED, VMDK, VPC, ISO, BOCHS, CLOOP, DMG, };

        std::string get_storage_pool_type_string(Config::Impl::Datatype::StoragePoolType type);
        std::string get_storage_volume_type_string(Config::Impl::Datatype::StorageVolumeType type);
        std::string get_storage_unit_string(Config::Impl::Datatype::StorageUnit unit);
        std::string get_file_format_type_string(Config::Impl::Datatype::FileFormatType format_type);
      }
    }
  }
}
