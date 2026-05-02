#pragma once

#include <vector>
#include <VirtXX/Impl/datatypes.hxx>
#include <libvirt/libvirt.h>
#include <VirtXX/Impl/ErrorBlock.hxx>
#include <VirtXX/Impl/Config/DomainConfig.hxx>
#include <VirtXX/Impl/LibvirtConnectionCreationKey.hxx>


namespace VirtXX {
  namespace Impl {
    class LibvirtConnection;

    class LibvirtDomain {
    private:
      datatype::LibvirtInternalDomainPtr m_DomainPtr;
      mutable ErrorBlock m_LastError;

      void report_error(datatype::ErrorCode code, datatype::ErrorMsg msg) const;

    public:
      LibvirtDomain([[maybe_unused]] LibvirtConnectionCreationKey, virDomainPtr domain_ptr);
      ~LibvirtDomain();
      LibvirtDomain(LibvirtDomain &&) noexcept = default;
      LibvirtDomain &operator=(LibvirtDomain &&) noexcept = default;
      LibvirtDomain(const LibvirtDomain &) = default;
      LibvirtDomain &operator=(const LibvirtDomain &) = default;

      explicit operator bool() const;

      [[nodiscard]] virDomainPtr get_handle() const;
      /*
       * Lifecycle Management
       * */
      std::int8_t start(std::vector<virDomainCreateFlags> flags={});
      std::int8_t shutdown(std::vector<virDomainShutdownFlagValues> flags={});
      std::int8_t restart(std::vector<virDomainRebootFlagValues> flags={});
      std::int8_t destroy(std::vector<virDomainDestroyFlagsValues> flags={}); // force shutdown
      std::int8_t force_shutdown(std::vector<virDomainDestroyFlagsValues> flags={}); // same as destroy
      std::int8_t suspend();
      std::int8_t resume();

      /*
       * Information Retrieval
       * */
      [[nodiscard]] std::string get_name() const;
      [[nodiscard]] std::int32_t get_id() const;
      [[nodiscard]] datatype::UUIDBytes get_uuid() const;
      [[nodiscard]] std::string get_uuid_string() const;
      [[nodiscard]] VirtXX::Impl::Config::DomainConfig get_xml_config(std::vector<virDomainXMLFlags> flags={}) const;
      [[nodiscard]] virDomainState get_state() const;
      [[nodiscard]] std::string get_state_string() const;
      [[nodiscard]] std::int32_t get_status_reason() const;
      [[nodiscard]] virDomainInfo get_info() const;

      [[nodiscard]] ErrorBlock get_last_error() const;
    };
  }
}
