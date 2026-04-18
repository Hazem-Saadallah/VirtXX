#pragma once

#include <array>
#include <memory>
#include <string>
#include <vector>
#include <cstdint>
#include <libvirt/virterror.h>
#include <VirtXX/Impl/Deleters.hxx>

namespace VirtXX {
  namespace Impl {
    class LibvirtDomain;
    class LibvirtStoragePool;
    class LibvirtStorageVolume;

    namespace datatype {
      enum class ErrorCode : std::uint8_t {
        NONE=0,
        NULL_CONNECTION_PTR,
        NULL_DOMAIN_PTR,
        LIBVIRT_INTERNAL_ERROR,
        DOMAIN_START_SUCCESSFUL,
        DOMAIN_START_FAILED,
        DOMAIN_SHUTDOWN_SUCCESSFUL,
        DOMAIN_SHUTDOWN_FAILED,
      };
      typedef std::string ErrorMsg;
      // typedef std::pair<ErrorCode_t, ErrorMsg_t> Error_t;

      // typedef virErrorNumber LibvirtErrorCode_t;
      // typedef std::string LibvirtErrorMsg_t;
      // typedef std::pair<LibvirtErrorCode_t, LibvirtErrorMsg_t> LibvirtError_t;

      typedef std::shared_ptr<virError> LibvirtInternalErrorPtr;
      typedef std::shared_ptr<virDomain> LibvirtInternalDomainPtr;
      typedef std::shared_ptr<virConnect> LibvirtInternalConnectionPtr;
      typedef std::shared_ptr<virStoragePool> LibvirtInternalStoragePoolPtr;
      typedef std::shared_ptr<virStorageVol> LibvirtInternalStorageVolumePtr;

      typedef std::vector<LibvirtDomain> DomainList;
      typedef std::vector<LibvirtStoragePool> StoragePoolList;
      typedef std::vector<LibvirtStorageVolume> StorageVolumeList;
      typedef std::array<std::uint8_t, VIR_UUID_BUFLEN> UUIDBytes;
    }
  }
}
