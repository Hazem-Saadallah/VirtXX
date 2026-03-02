#pragma once

#include <array>
#include <memory>
#include <cstdint>
#include <string>
#include <libvirt/virterror.h>
#include <Deleters.hxx>

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
  typedef std::array<std::uint8_t, VIR_UUID_BUFLEN> _UUIDBytes;
}
