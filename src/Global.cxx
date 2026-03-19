#include <cstddef>
#include <libvirt/virterror.h>
#include <Global.hxx>

void Global::SilenceStderrReporting() {
  virSetErrorFunc(NULL, NULL);
}
