#include <cmath>
#include <cstdint>
#include <string>
#include <numeric>
#include <functional>
#include <VirtXX/Impl/datatypes.hxx>
#include <libvirt/libvirt.h>
#include <libvirt/virterror.h>
#include <VirtXX/Impl/ErrMsg.hxx>
#include <VirtXX/Impl/Misc.hxx>
#include <VirtXX/Impl/LibvirtDomain.hxx>
#include <VirtXX/Impl/LibvirtConnectionCreationKey.hxx>

VirtXX::Impl::LibvirtDomain::LibvirtDomain([[maybe_unused]] LibvirtConnectionCreationKey, virDomainPtr domain_ptr)
: m_DomainPtr(domain_ptr, Deleters::LibvirtDomainPtrDeleter()), m_LastError(datatype::ErrorCode::NONE, ErrMsg::not_an_error) { }

VirtXX::Impl::LibvirtDomain::~LibvirtDomain() = default;

void VirtXX::Impl::LibvirtDomain::report_error(datatype::ErrorCode code, datatype::ErrorMsg msg) const {
  m_LastError = ErrorBlock(code, msg);
}

VirtXX::Impl::LibvirtDomain::operator bool() const { return m_DomainPtr != nullptr; }

virDomainPtr VirtXX::Impl::LibvirtDomain::get_handle() const { return m_DomainPtr.get(); }

[[nodiscard]] VirtXX::Impl::ErrorBlock VirtXX::Impl::LibvirtDomain::get_last_error() const { return m_LastError; }

std::int8_t VirtXX::Impl::LibvirtDomain::start(std::vector<virDomainCreateFlags> flags) {
  REPORT_AND_RETURN_IF_NULL_HANDLE(-1);
  std::int8_t res = virDomainCreateWithFlags(get_handle(), std::accumulate(flags.begin(), flags.end(),
                                                                           static_cast<std::uint8_t>(VIR_DOMAIN_NONE),
                                                                           std::bit_or<std::uint8_t>()));
  REPORT_IF_INTERNEL_ERROR(res);
  return res;
}

std::int8_t VirtXX::Impl::LibvirtDomain::shutdown(std::vector<virDomainShutdownFlagValues> flags) {
  REPORT_AND_RETURN_IF_NULL_HANDLE(-1);
  std::int8_t res = virDomainShutdownFlags(get_handle(),
                                            std::accumulate(flags.begin(), flags.end(),
                                                            static_cast<std::uint8_t>(VIR_DOMAIN_SHUTDOWN_DEFAULT),
                                                            std::bit_or<std::uint8_t>()));
  REPORT_IF_INTERNEL_ERROR(res);
  return res;
}

std::int8_t VirtXX::Impl::LibvirtDomain::restart(std::vector<virDomainRebootFlagValues> flags) {
  REPORT_AND_RETURN_IF_NULL_HANDLE(-1);
  std::int8_t res = virDomainReboot(get_handle(), std::accumulate(flags.begin(), flags.end(),
                                                                   static_cast<std::uint8_t>(VIR_DOMAIN_REBOOT_DEFAULT),
                                                                   std::bit_or<std::uint8_t>()));
  REPORT_IF_INTERNEL_ERROR(res);
  return res;
}

std::int8_t VirtXX::Impl::LibvirtDomain::destroy(std::vector<virDomainDestroyFlagsValues> flags) {
  REPORT_AND_RETURN_IF_NULL_HANDLE(-1);
  std::int8_t res = virDomainDestroyFlags(get_handle(),
                                           std::accumulate(flags.begin(), flags.end(),
                                                           static_cast<std::uint8_t>(VIR_DOMAIN_DESTROY_DEFAULT),
                                                           std::bit_or<std::uint8_t>()));
  REPORT_IF_INTERNEL_ERROR(res);
  return res;
}

std::int8_t VirtXX::Impl::LibvirtDomain::force_shutdown(std::vector<virDomainDestroyFlagsValues> flags) {
  return destroy(flags);
} // same as destroy

std::int8_t VirtXX::Impl::LibvirtDomain::suspend() {
  REPORT_AND_RETURN_IF_NULL_HANDLE(-1);
  std::int8_t res = virDomainSuspend(get_handle());
  REPORT_IF_INTERNEL_ERROR(res);
  return res;
}

std::int8_t VirtXX::Impl::LibvirtDomain::resume() {
  REPORT_AND_RETURN_IF_NULL_HANDLE(-1);
  std::int8_t res = virDomainResume(get_handle());
  REPORT_IF_INTERNEL_ERROR(res);
  return res;
}

std::string VirtXX::Impl::LibvirtDomain::get_name() const {
  REPORT_AND_RETURN_IF_NULL_HANDLE(std::string());
  return std::string(virDomainGetName(get_handle()));
}
std::int32_t VirtXX::Impl::LibvirtDomain::get_id() const {
  REPORT_AND_RETURN_IF_NULL_HANDLE(-1);
  std::uint32_t res = virDomainGetID(get_handle());
  REPORT_IF_INTERNEL_ERROR(res);
  return res;
}

VirtXX::Impl::datatype::UUIDBytes VirtXX::Impl::LibvirtDomain::get_uuid() const {
  REPORT_AND_RETURN_IF_NULL_HANDLE(datatype::UUIDBytes());
  datatype::UUIDBytes buffer = {0};
  std::int8_t res = virDomainGetUUID(get_handle(), buffer.data());
  REPORT_IF_INTERNEL_ERROR(res);
  return buffer;
}

std::string VirtXX::Impl::LibvirtDomain::get_uuid_string() const {
  REPORT_AND_RETURN_IF_NULL_HANDLE(std::string());
  std::string buffer(VIR_UUID_STRING_BUFLEN, '\0');
  std::int8_t res = virDomainGetUUIDString(get_handle(), buffer.data());
  REPORT_IF_INTERNEL_ERROR(res);
  return buffer;
}

VirtXX::Impl::Config::DomainConfig VirtXX::Impl::LibvirtDomain::get_xml_config(std::vector<virDomainXMLFlags> flags) const {
  REPORT_AND_RETURN_IF_NULL_HANDLE(VirtXX::Impl::Config::DomainConfig());
  char *raw_xml = virDomainGetXMLDesc(get_handle(), std::accumulate(flags.begin(), flags.end(), 0, std::bit_or<std::uint8_t>()));
  if(!raw_xml) return VirtXX::Impl::Config::DomainConfig();
  VirtXX::Impl::Config::DomainConfig domain_config;
  domain_config.load_string(std::string(raw_xml));
  std::free(raw_xml);
  return domain_config;
}

virDomainState VirtXX::Impl::LibvirtDomain::get_state() const {
  virDomainState state = virDomainState();
  REPORT_AND_RETURN_IF_NULL_HANDLE(state);
  std::int8_t res = virDomainGetState(get_handle(), reinterpret_cast<int*>(&state), NULL, 0);
  REPORT_IF_INTERNEL_ERROR(res);
  return state;
}

std::string VirtXX::Impl::LibvirtDomain::get_state_string() const {
  switch (get_state()) {
    case VIR_DOMAIN_NOSTATE: return std::string("No State"); break;
    case VIR_DOMAIN_RUNNING: return std::string("Running"); break;
    case VIR_DOMAIN_BLOCKED: return std::string("Blocked"); break;
    case VIR_DOMAIN_PAUSED: return std::string("Paused"); break;
    case VIR_DOMAIN_SHUTDOWN: return std::string("Shutdown"); break;
    case VIR_DOMAIN_SHUTOFF: return std::string("Shutoff"); break; 
    case VIR_DOMAIN_CRASHED: return std::string("Crashed"); break; 
    case VIR_DOMAIN_PMSUSPENDED: return std::string("Power-Management Suspend"); break;

# ifdef VIR_ENUM_SENTINELS
    case VIR_DOMAIN_LAST: return std::string("Last"); break;
# endif
  }
  return std::string("Unknown");
}

std::int32_t VirtXX::Impl::LibvirtDomain::get_status_reason() const {
  REPORT_AND_RETURN_IF_NULL_HANDLE(-1);
  std::int32_t state=std::int32_t(), reason=std::int32_t();
  std::int8_t res = virDomainGetState(get_handle(), &state, &reason, 0);
  REPORT_IF_INTERNEL_ERROR(res);
  return reason;
}

std::int64_t VirtXX::Impl::LibvirtDomain::get_vcpu(std::vector<virDomainVcpuFlags> flags) const {
  REPORT_AND_RETURN_IF_NULL_HANDLE(-1);
  std::uint64_t res = virDomainGetVcpusFlags(get_handle(), std::accumulate(flags.begin(), flags.end(), static_cast<std::uint8_t>(VIR_DOMAIN_VCPU_CURRENT), std::bit_or<std::uint8_t>()));
  REPORT_IF_INTERNEL_ERROR(res);
  return res;
}

std::double_t VirtXX::Impl::LibvirtDomain::get_max_memory(datatype::SizeType size_unit) const {
  REPORT_AND_RETURN_IF_NULL_HANDLE(-1);
  std::uint64_t result = virDomainGetMaxMemory(get_handle())*1024ULL; /* Size in Bytes */
  if(static_cast<std::int32_t>(result) == 0)
    report_error(datatype::ErrorCode::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error);

  std::double_t div = std::powf(1024, static_cast<std::int32_t>(size_unit));
  return static_cast<std::double_t>(result)/div;
}

virDomainInfo VirtXX::Impl::LibvirtDomain::get_info() const {
  virDomainInfo info;
  REPORT_AND_RETURN_IF_NULL_HANDLE(info);
  std::int8_t res = virDomainGetInfo(get_handle(), &info);
  REPORT_IF_INTERNEL_ERROR(res);
  return info;
}

std::int8_t VirtXX::Impl::LibvirtDomain::set_vcpu(std::uint32_t nvcpus, std::vector<virDomainVcpuFlags> flags) {
  REPORT_AND_RETURN_IF_NULL_HANDLE(-1);
  std::uint32_t result = virDomainSetVcpusFlags(get_handle(), nvcpus, std::accumulate(flags.begin(), flags.end(), static_cast<std::uint8_t>(VIR_DOMAIN_VCPU_CURRENT), std::bit_or<std::uint8_t>()));
  REPORT_IF_INTERNEL_ERROR(result);
  return result;
}

std::int8_t VirtXX::Impl::LibvirtDomain::set_memory(std::uint64_t memory, datatype::SizeType size_unit, std::vector<virDomainMemoryModFlags> flags) {
  REPORT_AND_RETURN_IF_NULL_HANDLE(-1);
  std::uint64_t size_bytes = memory * std::powl(1024, static_cast<std::uint8_t>(size_unit));
  std::int8_t result = virDomainSetMemoryFlags(get_handle(), size_bytes/1024, std::accumulate(flags.begin(), flags.end(), static_cast<std::uint8_t>(VIR_DOMAIN_MEM_CURRENT), std::bit_or<std::uint8_t>()));
  REPORT_IF_INTERNEL_ERROR(result);
  return result;
}
