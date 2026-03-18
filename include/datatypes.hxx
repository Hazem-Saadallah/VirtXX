#pragma once

#include <array>
#include <memory>
#include <string>
#include <vector>
#include <cstdint>
#include <libvirt/virterror.h>
#include <Deleters.hxx>
class _LibvirtDomain;
class _LibvirtStoragePool;
class _LibvirtStorageVolume;

namespace _datatype {
  enum class ErrorCode_t : std::uint8_t {
    NONE=0,
    NULL_CONNECTION_PTR,
    NULL_DOMAIN_PTR,
    LIBVIRT_INTERNAL_ERROR,
    DOMAIN_START_SUCCESSFUL,
    DOMAIN_START_FAILED,
    DOMAIN_SHUTDOWN_SUCCESSFUL,
    DOMAIN_SHUTDOWN_FAILED,
  };
  typedef std::string ErrorMsg_t;
  // typedef std::pair<ErrorCode_t, ErrorMsg_t> Error_t;

  // typedef virErrorNumber LibvirtErrorCode_t;
  // typedef std::string LibvirtErrorMsg_t;
  // typedef std::pair<LibvirtErrorCode_t, LibvirtErrorMsg_t> LibvirtError_t;

  typedef std::shared_ptr<virError> _LibvirtInternalErrorPtr;
  typedef std::shared_ptr<virDomain> _LibvirtInternalDomainPtr;
  typedef std::shared_ptr<virConnect> _LibvirtInternalConnectionPtr;
  typedef std::shared_ptr<virStoragePool> _LibvirtInternalStoragePoolPtr;
  typedef std::shared_ptr<virStorageVol> _LibvirtInternalStorageVolumePtr;

  typedef std::vector<_LibvirtDomain> _DomainList;
  typedef std::vector<_LibvirtStoragePool> _StoragePoolList;
  typedef std::vector<_LibvirtStorageVolume> _StorageVolumeList;
  typedef std::array<std::uint8_t, VIR_UUID_BUFLEN> _UUIDBytes;
}
