#include <cstddef>
#include <libvirt/virterror.h>
#include <Global.hxx>

void _SilentErrorHandler([[maybe_unused]] void *userData, [[maybe_unused]] virErrorPtr error) { }

void Global::SilenceStderrReporting() {
  virSetErrorFunc(NULL, _SilentErrorHandler);
}
