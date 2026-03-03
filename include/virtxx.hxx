#pragma once

#include <LibvirtConnection.hxx>
#include <LibvirtDomain.hxx>
#include <datatypes.hxx>

namespace virtxx {
  typedef _LibvirtConnection Connection;
  typedef _LibvirtDomain Domain;
  typedef _ErrorBlock Error;
  typedef _datatype::_UUIDBytes UUIDBytes;
}
