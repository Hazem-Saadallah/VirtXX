#include <VirtXX/Impl/Config/Datatype.hxx>

std::string Config::Impl::Datatype::get_storage_pool_type_string(Config::Impl::Datatype::StoragePoolType type) {
  switch (type) {
    case Config::Impl::Datatype::StoragePoolType::DIRECTORY: return std::string("dir"); break;
    case Config::Impl::Datatype::StoragePoolType::FILESYSTEM: return std::string("fs"); break;
    case Config::Impl::Datatype::StoragePoolType::NETWORK_FILESYSTEM: return std::string("netfs"); break;
    case Config::Impl::Datatype::StoragePoolType::LOGICAL_VOLUME_MANAGER: return std::string("logical"); break;
    case Config::Impl::Datatype::StoragePoolType::DISK: return std::string("disk"); break;
    case Config::Impl::Datatype::StoragePoolType::ISCSI: return std::string("iscsi"); break;
    case Config::Impl::Datatype::StoragePoolType::ISCSI_DIRECT: return std::string("iscsi-direct"); break;
    case Config::Impl::Datatype::StoragePoolType::SCSI: return std::string("scsi"); break;
    case Config::Impl::Datatype::StoragePoolType::MULTIPATH: return std::string("mpath"); break;
    case Config::Impl::Datatype::StoragePoolType::CEPH: [[fallthrough]];
    case Config::Impl::Datatype::StoragePoolType::RBD: return std::string("rbd"); break;
    case Config::Impl::Datatype::StoragePoolType::SHEEPDOG: return std::string("sheepdog"); break;
    case Config::Impl::Datatype::StoragePoolType::GLUSTER: return std::string("gluster"); break;
    case Config::Impl::Datatype::StoragePoolType::ZFS: return std::string("zfs"); break;
    case Config::Impl::Datatype::StoragePoolType::VSTORAGE: return std::string("vstorage"); break;
  }
  return std::string("");
}

std::string Config::Impl::Datatype::get_storage_volume_type_string(Config::Impl::Datatype::StorageVolumeType type) {
  switch (type) {
    case Config::Impl::Datatype::StorageVolumeType::FILE: return std::string("file"); break;
    case Config::Impl::Datatype::StorageVolumeType::BLOCK: return std::string("block"); break;
    case Config::Impl::Datatype::StorageVolumeType::DIRECTORY: return std::string("dir"); break;
    case Config::Impl::Datatype::StorageVolumeType::NETWORK: return std::string("network"); break;
    case Config::Impl::Datatype::StorageVolumeType::NETDIR: return std::string("netdir"); break;
    case Config::Impl::Datatype::StorageVolumeType::PLOOP: return std::string("ploop"); break;
  }
  return std::string();
}

std::string Config::Impl::Datatype::get_storage_unit_string(Config::Impl::Datatype::StorageUnit unit) {
  switch (unit) {
    case Config::Impl::Datatype::StorageUnit::BYTES: return std::string("bytes"); break;
    case Config::Impl::Datatype::StorageUnit::B: return std::string("B"); break;
    case Config::Impl::Datatype::StorageUnit::KIB: return std::string("KiB"); break;
    case Config::Impl::Datatype::StorageUnit::K: return std::string("K"); break;
    case Config::Impl::Datatype::StorageUnit::KB: return std::string("KB"); break;
    case Config::Impl::Datatype::StorageUnit::MIB: return std::string("KiB"); break;
    case Config::Impl::Datatype::StorageUnit::M: return std::string("M"); break;
    case Config::Impl::Datatype::StorageUnit::MB: return std::string("MB"); break;
    case Config::Impl::Datatype::StorageUnit::GIB: return std::string("GiB"); break;
    case Config::Impl::Datatype::StorageUnit::G: return std::string("G"); break;
    case Config::Impl::Datatype::StorageUnit::GB: return std::string("GB"); break;
    case Config::Impl::Datatype::StorageUnit::TIB: return std::string("TiB"); break;
    case Config::Impl::Datatype::StorageUnit::T: return std::string("T"); break;
    case Config::Impl::Datatype::StorageUnit::TB: return std::string("TB"); break;
    case Config::Impl::Datatype::StorageUnit::PIB: return std::string("PiB"); break;
    case Config::Impl::Datatype::StorageUnit::P: return std::string("P"); break;
    case Config::Impl::Datatype::StorageUnit::PB: return std::string("PB"); break;
    case Config::Impl::Datatype::StorageUnit::EIB: return std::string("EiB"); break;
    case Config::Impl::Datatype::StorageUnit::E: return std::string("E"); break;
    case Config::Impl::Datatype::StorageUnit::EB: return std::string("EB"); break;
  }
  return std::string();
}

std::string Config::Impl::Datatype::get_file_format_type_string(Config::Impl::Datatype::FileFormatType format_type) {
  switch (format_type) {
    case Config::Impl::Datatype::FileFormatType::RAW: return std::string("raw"); break;
    case Config::Impl::Datatype::FileFormatType::QCOW2: return std::string("qcow2"); break;
    case Config::Impl::Datatype::FileFormatType::QCOW: return std::string("qcow"); break;
    case Config::Impl::Datatype::FileFormatType::QED: return std::string("qed"); break;
    case Config::Impl::Datatype::FileFormatType::VMDK: return std::string("vmdk"); break;
    case Config::Impl::Datatype::FileFormatType::VPC: return std::string("vpc"); break;
    case Config::Impl::Datatype::FileFormatType::ISO: return std::string("iso"); break;
    case Config::Impl::Datatype::FileFormatType::BOCHS: return std::string("bochs"); break;
    case Config::Impl::Datatype::FileFormatType::CLOOP: return std::string("cloop"); break;
    case Config::Impl::Datatype::FileFormatType::DMG: return std::string("dmg"); break;
  }
  return std::string();
}
