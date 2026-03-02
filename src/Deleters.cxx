#include <Deleters.hxx>


void Deleters::_LibvirtConnectionPtrDeleter::operator()(virConnectPtr connection_ptr) const {
  virConnectClose(connection_ptr);
}

void Deleters::_LibvirtDomainPtrDeleter::operator()(virDomainPtr domain_ptr) const {
  virDomainFree(domain_ptr);
}

void Deleters::_LibvirtErrorPtrDeleter::operator()(virErrorPtr error_ptr) const {
  virResetError(error_ptr);
}
