#include <cstddef>
#include <libvirt/virterror.h>
#include <VirtXX/Impl/Global.hxx>

void _SilentErrorHandler([[maybe_unused]] void *userData, [[maybe_unused]] virErrorPtr error) { }

void VirtXX::Impl::Global::SilenceStderrReporting() { virSetErrorFunc(NULL, _SilentErrorHandler); }
