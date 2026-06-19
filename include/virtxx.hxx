#pragma once

#include <VirtXX/Impl/Global.hxx>
#include <VirtXX/Impl/XMLConfig.hxx>
#include <VirtXX/Impl/datatypes.hxx>
#include <VirtXX/Impl/LibvirtDomain.hxx>
#include <VirtXX/Impl/LibvirtConnection.hxx>
#include <VirtXX/Impl/Config/StoragePoolConfig.hxx>
#include <VirtXX/Impl/Config/StorageVolumeConfig.hxx>

namespace virtxx {
typedef VirtXX::Impl::LibvirtConnection Connection;
typedef VirtXX::Impl::LibvirtDomain Domain;
typedef VirtXX::Impl::ErrorBlock Error;
typedef VirtXX::Impl::LibvirtStoragePool StoragePool;
typedef VirtXX::Impl::LibvirtStorageVolume StorageVolume;

typedef VirtXX::Impl::datatype::UUIDBytes UUIDBytes;
typedef VirtXX::Impl::datatype::DomainList DomainList;
typedef VirtXX::Impl::datatype::StoragePoolList StoragePoolList;
typedef VirtXX::Impl::datatype::StorageVolumeList StorageVolumeList;
typedef VirtXX::Impl::datatype::ErrorCode ErrorCode;
typedef VirtXX::Impl::datatype::SizeType SizeType;
typedef VirtXX::Impl::datatype::LibvirtInternalErrorPtr LibvirtErrorPtr;

namespace XMLConfig = VirtXX::Impl::XMLConfig;
namespace Global = VirtXX::Impl::Global;

namespace Config = VirtXX::Impl::Config;
}
