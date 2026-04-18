#include <VirtXX/Impl/Config/Datatype.hxx>

std::string VirtXX::Config::Impl::Datatype::get_storage_pool_type_string(Config::Impl::Datatype::StoragePoolType type) {
  switch (type) {
    case StoragePoolType::DIRECTORY: return std::string("dir"); break;
    case StoragePoolType::FILESYSTEM: return std::string("fs"); break;
    case StoragePoolType::NETWORK_FILESYSTEM: return std::string("netfs"); break;
    case StoragePoolType::LOGICAL_VOLUME_MANAGER: return std::string("logical"); break;
    case StoragePoolType::DISK: return std::string("disk"); break;
    case StoragePoolType::ISCSI: return std::string("iscsi"); break;
    case StoragePoolType::ISCSI_DIRECT: return std::string("iscsi-direct"); break;
    case StoragePoolType::SCSI: return std::string("scsi"); break;
    case StoragePoolType::MULTIPATH: return std::string("mpath"); break;
    case StoragePoolType::CEPH: [[fallthrough]];
    case StoragePoolType::RBD: return std::string("rbd"); break;
    case StoragePoolType::SHEEPDOG: return std::string("sheepdog"); break;
    case StoragePoolType::GLUSTER: return std::string("gluster"); break;
    case StoragePoolType::ZFS: return std::string("zfs"); break;
    case StoragePoolType::VSTORAGE: return std::string("vstorage"); break;
  }
  return std::string("");
}

std::string VirtXX::Config::Impl::Datatype::get_storage_volume_type_string(Config::Impl::Datatype::StorageVolumeType type) {
  switch (type) {
    case StorageVolumeType::FILE: return std::string("file"); break;
    case StorageVolumeType::BLOCK: return std::string("block"); break;
    case StorageVolumeType::DIRECTORY: return std::string("dir"); break;
    case StorageVolumeType::NETWORK: return std::string("network"); break;
    case StorageVolumeType::NETDIR: return std::string("netdir"); break;
    case StorageVolumeType::PLOOP: return std::string("ploop"); break;
  }
  return std::string();
}

std::string VirtXX::Config::Impl::Datatype::get_storage_unit_string(Config::Impl::Datatype::StorageUnit unit) {
  switch (unit) {
    case StorageUnit::BYTES: return std::string("bytes"); break;
    case StorageUnit::B: return std::string("B"); break;
    case StorageUnit::KIB: return std::string("KiB"); break;
    case StorageUnit::K: return std::string("K"); break;
    case StorageUnit::KB: return std::string("KB"); break;
    case StorageUnit::MIB: return std::string("KiB"); break;
    case StorageUnit::M: return std::string("M"); break;
    case StorageUnit::MB: return std::string("MB"); break;
    case StorageUnit::GIB: return std::string("GiB"); break;
    case StorageUnit::G: return std::string("G"); break;
    case StorageUnit::GB: return std::string("GB"); break;
    case StorageUnit::TIB: return std::string("TiB"); break;
    case StorageUnit::T: return std::string("T"); break;
    case StorageUnit::TB: return std::string("TB"); break;
    case StorageUnit::PIB: return std::string("PiB"); break;
    case StorageUnit::P: return std::string("P"); break;
    case StorageUnit::PB: return std::string("PB"); break;
    case StorageUnit::EIB: return std::string("EiB"); break;
    case StorageUnit::E: return std::string("E"); break;
    case StorageUnit::EB: return std::string("EB"); break;
  }
  return std::string();
}

std::string VirtXX::Config::Impl::Datatype::get_file_format_type_string(Config::Impl::Datatype::FileFormatType format_type) {
  switch (format_type) {
    case FileFormatType::RAW: return std::string("raw"); break;
    case FileFormatType::QCOW2: return std::string("qcow2"); break;
    case FileFormatType::QCOW: return std::string("qcow"); break;
    case FileFormatType::QED: return std::string("qed"); break;
    case FileFormatType::VMDK: return std::string("vmdk"); break;
    case FileFormatType::VPC: return std::string("vpc"); break;
    case FileFormatType::ISO: return std::string("iso"); break;
    case FileFormatType::BOCHS: return std::string("bochs"); break;
    case FileFormatType::CLOOP: return std::string("cloop"); break;
    case FileFormatType::DMG: return std::string("dmg"); break;
  }
  return std::string();
}
