#pragma once

#include <VirtXX/Impl/XMLConfig.hxx>
#include <VirtXX/Impl/LibvirtConnection.hxx>
#include <VirtXX/Impl/LibvirtDomain.hxx>
#include <VirtXX/Impl/datatypes.hxx>
#include <VirtXX/Impl/Global.hxx>

namespace virtxx {
  typedef _LibvirtConnection Connection;
  typedef _LibvirtDomain Domain;
  typedef _ErrorBlock Error;
  typedef _LibvirtStoragePool StoragePool;
  typedef _LibvirtStorageVolume StorageVolume;

  typedef _datatype::_UUIDBytes UUIDBytes;
  typedef _datatype::_DomainList DomainList;
  typedef _datatype::_StoragePoolList StoragePoolList;
  typedef _datatype::_StorageVolumeList StorageVolumeList;
  typedef _datatype::ErrorCode_t ErrorCode;

  namespace XMLConfig = ::_XMLConfig;
  namespace Global = ::Global;
}
