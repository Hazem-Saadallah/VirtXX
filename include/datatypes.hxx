#pragma once

#include <array>
#include <memory>
#include <string>
#include <vector>
#include <cstdint>
#include <libvirt/virterror.h>
#include <Deleters.hxx>

#define REPORT_AND_RETURN_IF_NULL_HANDLE(return_value)                                 \
  do {                                                                                 \
    if(!get_handle()) {                                                                \
      report_error(_datatype::ErrorCode_t::NULL_DOMAIN_PTR , ErrMsg::null_domain_ptr); \
      return return_value;                                                             \
    }                                                                                  \
  } while(false)

#define REPORT_IF_INTERNEL_ERROR(result) \
  if(static_cast<std::int32_t>(result) < 0) report_error(_datatype::ErrorCode_t::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error)

#define REPORT_AND_RETURN_IF_INTERNEL_ERROR(result, return_value)                                   \
  do {                                                                                              \
    if(static_cast<std::int32_t>(result) < 0) {                                                     \
      report_error(_datatype::ErrorCode_t::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error); \
      return return_value;                                                                          \
    }                                                                                               \
  } while(false)

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

  typedef std::unique_ptr<virError, Deleters::_LibvirtErrorPtrDeleter> _LibvirtInternalErrorPtr;
  typedef std::unique_ptr<virDomain, Deleters::_LibvirtDomainPtrDeleter> _LibvirtInternalDomainPtr;
  typedef std::unique_ptr<virConnect, Deleters::_LibvirtConnectionPtrDeleter> _LibvirtInternalConnectionPtr;
  typedef std::unique_ptr<virStoragePool, Deleters::_LibvirtStoragePoolPtrDeleter> _LibvirtInternalStoragePoolPtr;
  typedef std::unique_ptr<virStorageVol, Deleters::_LibvirtStorageVolumePtrDeleter> _LibvirtInternalStorageVolumePtr;

  typedef std::vector<_LibvirtDomain> _DomainList;
  typedef std::vector<_LibvirtStoragePool> _StoragePoolList;
  typedef std::vector<_LibvirtStorageVolume> _StorageVolumeList;
  typedef std::array<std::uint8_t, VIR_UUID_BUFLEN> _UUIDBytes;
}
