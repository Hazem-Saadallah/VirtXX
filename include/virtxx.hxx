#pragma once

#include <XMLConfig.hxx>
#include <LibvirtConnection.hxx>
#include <LibvirtDomain.hxx>
#include <datatypes.hxx>
#include <Global.hxx>

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

  namespace XMLConfig = ::_XMLConfig;
  namespace Global = ::Global;
}
