#pragma once

#include <thread>
#include <atomic>
#include <unistd.h>
#include <termios.h>
#include <functional>
#include <string_view>
#include <libvirt/libvirt.h>
#include <libvirt/virterror.h>
#include <VirtXX/Impl/datatypes.hxx>
#include <VirtXX/Impl/LibvirtDomainCreationKey.hxx>

namespace VirtXX {
namespace Impl {
class LibvirtDomainConsole {
private:
  datatype::LibvirtInternalStreamPtr m_StreamPtr;
  std::atomic<bool> m_Active{false};
  std::thread m_ReaderThread;

public:
  using OutputCallback = std::function<void(std::string_view)>;
  // using InputProvider  = std::function<bool(std::string&)>;

public:
  LibvirtDomainConsole([[maybe_unused]] LibvirtDomainCreationKey key, virDomainPtr domain);
  ~LibvirtDomainConsole();

  LibvirtDomainConsole(const LibvirtDomainConsole&) = delete;
  LibvirtDomainConsole& operator=(const LibvirtDomainConsole&) = delete;

public:
  bool is_active() const;
  void stop();
  void start_listening(OutputCallback on_output);
  bool send_input(std::string_view data);
};
}
}
