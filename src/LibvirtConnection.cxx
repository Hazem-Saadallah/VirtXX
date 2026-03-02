#include <numeric>
#include <functional>
#include <libvirt/libvirt.h>
#include <libvirt/virterror.h>
#include <ErrMsg.hxx>
#include <datatypes.hxx>
#include <LibvirtConnection.hxx>
#include <LibvirtDomain.hxx>

_LibvirtConnection::_LibvirtConnection(virConnectPtr connection_ptr) : m_ConnectionPtr(connection_ptr) { }
_LibvirtConnection::_LibvirtConnection(const std::string& uri)
: m_ConnectionPtr(virConnectOpen(uri.c_str())), m_LastError(_datatype::ErrorCode_t::NONE, ErrMsg::not_an_error) { }

_LibvirtConnection::~_LibvirtConnection() = default; /* defined in here becasue the unique poiter is initialized here.*/

_LibvirtConnection::operator bool() const { return m_ConnectionPtr != nullptr; }

void _LibvirtConnection::report_error(_datatype::ErrorCode_t code, _datatype::ErrorMsg_t msg) {
  m_LastError = _ErrorBlock(code, msg);
}

virConnectPtr _LibvirtConnection::get_handle() const { return m_ConnectionPtr.get(); }

_ErrorBlock _LibvirtConnection::get_last_error() const { return m_LastError; }
virError _LibvirtConnection::get_last_libvirt_error() const { return m_LastLibvirtError; }

std::int32_t _LibvirtConnection::get_domain_count(std::vector<virConnectListAllDomainsFlags> flags) {
  std::int32_t count = virConnectListAllDomains(get_handle(), NULL, std::accumulate(flags.begin(), flags.end(),
                                                                                    0U, std::bit_or<std::uint8_t>()));
  if(count < 0) report_error(_datatype::ErrorCode_t::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error);
  return count;
}

_LibvirtDomain _LibvirtConnection::get_domain_by_name(const std::string& domain_name) const {
  return _LibvirtDomain(_LibvirtDomainCreationKey{}, virDomainLookupByName(get_handle(), domain_name.c_str()));
}
