#pragma once

#include <libvirt/virterror.h>

void _SilentErrorHandler([[maybe_unused]] void *userData, [[maybe_unused]] virErrorPtr error);

namespace Global {
  void SilenceStderrReporting();
  
}
