#pragma once

#include <VirtXX/Impl/Global.hxx>
#include <VirtXX/Impl/XMLConfig.hxx>
#include <VirtXX/Impl/datatypes.hxx>
#include <VirtXX/Impl/LibvirtDomain.hxx>
#include <VirtXX/Impl/LibvirtConnection.hxx>
#include <VirtXX/Impl/Config/StoragePoolConfig.hxx>
#include <VirtXX/Impl/Config/StorageVolumeConfig.hxx>

namespace virtxx {
  typedef VirtXX::Impl::_LibvirtConnection Connection;
  typedef VirtXX::Impl::_LibvirtDomain Domain;
  typedef VirtXX::Impl::_ErrorBlock Error;
  typedef VirtXX::Impl::_LibvirtStoragePool StoragePool;
  typedef VirtXX::Impl::_LibvirtStorageVolume StorageVolume;

  typedef VirtXX::Impl::_datatype::_UUIDBytes UUIDBytes;
  typedef VirtXX::Impl::_datatype::_DomainList DomainList;
  typedef VirtXX::Impl::_datatype::_StoragePoolList StoragePoolList;
  typedef VirtXX::Impl::_datatype::_StorageVolumeList StorageVolumeList;
  typedef VirtXX::Impl::_datatype::ErrorCode_t ErrorCode;

  typedef VirtXX::Config::Impl::StoragePoolConfig StoragePoolConfig;
  typedef VirtXX::Config::Impl::StorageVolumeConfig StorageVolumeConfig;

  namespace XMLConfig = VirtXX::Impl::_XMLConfig;
  namespace Global = VirtXX::Impl::Global;
}
