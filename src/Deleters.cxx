#include <Deleters.hxx>
#include <libvirt/libvirt.h>


void Deleters::_LibvirtConnectionPtrDeleter::operator()(virConnectPtr connection_ptr) const {
  virConnectClose(connection_ptr);
}

void Deleters::_LibvirtDomainPtrDeleter::operator()(virDomainPtr domain_ptr) const {
  virDomainFree(domain_ptr);
}

void Deleters::_LibvirtErrorPtrDeleter::operator()(virErrorPtr error_ptr) const {
  virFreeError(error_ptr);
}

void Deleters::_LibvirtStoragePoolPtrDeleter::operator()(virStoragePoolPtr storage_pool_ptr) const {
  virStoragePoolFree(storage_pool_ptr);
}

void Deleters::_LibvirtStorageVolumePtrDeleter::operator()(virStorageVolPtr storage_volume_ptr) const {
  virStorageVolFree(storage_volume_ptr);
}
