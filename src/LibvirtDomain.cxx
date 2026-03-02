#include "datatypes.hxx"
#include <LibvirtDomain.hxx>
#include <functional>
#include <libvirt/libvirt.h>
#include <libvirt/virterror.h>
#include <numeric>
#include <string>

#define REPORT_IF_NULL_HANDLE(return_value)                                          \
  if(!get_handle()) {                                                                \
    report_error(_datatype::ErrorCode_t::NULL_DOMAIN_PTR , ErrMsg::null_domain_ptr); \
    return return_value;                                                             \
  }
#define REPORT_IF_INTERNEL_ERROR() \
  if(res < 0) report_error(_datatype::ErrorCode_t::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error)

_LibvirtDomain::_LibvirtDomain([[maybe_unused]] _LibvirtDomainCreationKey, virDomainPtr domain_ptr)
: m_DomainPtr(domain_ptr), m_LastError(_datatype::ErrorCode_t::NONE, ErrMsg::not_an_error) { }

void _LibvirtDomain::report_error(_datatype::ErrorCode_t code, _datatype::ErrorMsg_t msg) {
  m_LastError = _ErrorBlock(code, msg);
}

virDomainPtr _LibvirtDomain::get_handle() { return m_DomainPtr.get(); }

std::int8_t _LibvirtDomain::start(std::vector<virDomainCreateFlags> flags) {
  REPORT_IF_NULL_HANDLE(-1);
  std::int8_t res = virDomainCreateWithFlags(get_handle(), std::accumulate(flags.begin(), flags.end(),
                                                                           static_cast<std::uint8_t>(VIR_DOMAIN_NONE),
                                                                           std::bit_or<std::uint8_t>()));
  REPORT_IF_INTERNEL_ERROR();
  return res;
}

std::int8_t _LibvirtDomain::shutdown(std::vector<virDomainShutdownFlagValues> flags) {
  REPORT_IF_NULL_HANDLE(-1);
  std::int8_t res = virDomainShutdownFlags(get_handle(),
                                            std::accumulate(flags.begin(), flags.end(),
                                                            static_cast<std::uint8_t>(VIR_DOMAIN_SHUTDOWN_DEFAULT),
                                                            std::bit_or<std::uint8_t>()));
  REPORT_IF_INTERNEL_ERROR();
  return res;
}

std::int8_t _LibvirtDomain::restart(std::vector<virDomainRebootFlagValues> flags) {
  REPORT_IF_NULL_HANDLE(-1);
  std::int8_t res = virDomainReboot(get_handle(), std::accumulate(flags.begin(), flags.end(),
                                                                   static_cast<std::uint8_t>(VIR_DOMAIN_REBOOT_DEFAULT),
                                                                   std::bit_or<std::uint8_t>()));
  REPORT_IF_INTERNEL_ERROR();
  return res;
}

std::int8_t _LibvirtDomain::destroy(std::vector<virDomainDestroyFlagsValues> flags) {
  REPORT_IF_NULL_HANDLE(-1);
  std::int8_t res = virDomainDestroyFlags(get_handle(),
                                           std::accumulate(flags.begin(), flags.end(),
                                                           static_cast<std::uint8_t>(VIR_DOMAIN_DESTROY_DEFAULT),
                                                           std::bit_or<std::uint8_t>()));
  REPORT_IF_INTERNEL_ERROR();
  return res;
}

std::int8_t _LibvirtDomain::force_shutdown(std::vector<virDomainDestroyFlagsValues> flags) {
  return destroy(flags);
} // same as destroy

std::int8_t _LibvirtDomain::suspend() {
  REPORT_IF_NULL_HANDLE(-1);
  std::int8_t res = virDomainSuspend(get_handle());
  REPORT_IF_INTERNEL_ERROR();
  return res;
}

std::int8_t _LibvirtDomain::resume() {
  REPORT_IF_NULL_HANDLE(-1);
  std::int8_t res = virDomainResume(get_handle());
  REPORT_IF_INTERNEL_ERROR();
  return res;
}

std::string _LibvirtDomain::get_name() {
  REPORT_IF_NULL_HANDLE(std::string());
  return std::string(virDomainGetName(get_handle()));
}
std::uint32_t _LibvirtDomain::get_id() { return virDomainGetID(get_handle()); }

_datatype::_UUIDBytes _LibvirtDomain::get_uuid() {
  REPORT_IF_NULL_HANDLE(_datatype::_UUIDBytes());
  _datatype::_UUIDBytes buffer = {0};
  std::int8_t res = virDomainGetUUID(get_handle(), buffer.data());
  REPORT_IF_INTERNEL_ERROR();
  return buffer;
}

std::string _LibvirtDomain::get_uuid_string() {
  REPORT_IF_NULL_HANDLE(std::string());
  std::string buffer(VIR_UUID_STRING_BUFLEN, '\0');
  std::int8_t res = virDomainGetUUIDString(get_handle(), buffer.data());
  REPORT_IF_INTERNEL_ERROR();
  return buffer;
}

std::string _LibvirtDomain::get_xml_config(std::vector<virDomainXMLFlags> flags) {
  REPORT_IF_NULL_HANDLE(std::string());
  char *raw_xml = virDomainGetXMLDesc(get_handle(), std::accumulate(flags.begin(), flags.end(),
                                                                    0, std::bit_or<std::uint8_t>()));
  if(!raw_xml) return std::string();
  std::string res = std::string(raw_xml);
  std::free(raw_xml);
  return res;
}

virDomainState _LibvirtDomain::get_status() {
  virDomainState state = virDomainState();
  REPORT_IF_NULL_HANDLE(state);
  std::int8_t res = virDomainGetState(get_handle(), reinterpret_cast<int*>(&state), NULL, 0);
  REPORT_IF_INTERNEL_ERROR();
  return state;
}

std::int32_t _LibvirtDomain::get_status_reason() {
  REPORT_IF_NULL_HANDLE(-1);
  std::int32_t state=std::int32_t(), reason=std::int32_t();
  std::int8_t res = virDomainGetState(get_handle(), &state, &reason, 0);
  REPORT_IF_INTERNEL_ERROR();
  return reason;
  virDomainGetInfo(get_handle(), NULL);
}

virDomainInfo _LibvirtDomain::get_info() {
  virDomainInfo info;
  REPORT_IF_NULL_HANDLE(info);
  std::int8_t res = virDomainGetInfo(get_handle(), &info);
  REPORT_IF_INTERNEL_ERROR();
  return info;
}
