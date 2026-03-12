#pragma once

#include <vector>
#include <datatypes.hxx>
#include <libvirt/libvirt.h>
#include <ErrorBlock.hxx>
#include <LibvirtConnectionCreationKey.hxx>

class _LibvirtConnection;

class _LibvirtDomain {
private:
  _datatype::_LibvirtInternalDomainPtr m_DomainPtr;
  _ErrorBlock m_LastError;

  void report_error(_datatype::ErrorCode_t code, _datatype::ErrorMsg_t msg);

public:
  _LibvirtDomain([[maybe_unused]] _LibvirtConnectionCreationKey, virDomainPtr domain_ptr);
  ~_LibvirtDomain();

  _LibvirtDomain(_LibvirtDomain &&) noexcept = default;
  _LibvirtDomain &operator=(_LibvirtDomain &&) noexcept = default;

  _LibvirtDomain(const _LibvirtDomain &) = delete;
  _LibvirtDomain &operator=(const _LibvirtDomain &) = delete;

  explicit operator bool() const;

  [[nodiscard]] virDomainPtr get_handle();
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
  [[nodiscard]] std::string get_name();
  [[nodiscard]] std::int32_t get_id();
  [[nodiscard]] _datatype::_UUIDBytes get_uuid();
  [[nodiscard]] std::string get_uuid_string();
  [[nodiscard]] std::string get_xml_config(std::vector<virDomainXMLFlags> flags={});
  [[nodiscard]] virDomainState get_status();
  [[nodiscard]] std::int32_t get_status_reason();
  [[nodiscard]] virDomainInfo get_info();

  [[nodiscard]] _ErrorBlock get_last_error() const;
};
