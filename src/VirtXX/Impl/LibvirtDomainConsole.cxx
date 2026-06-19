#include <thread>
#include <atomic>
#include <unistd.h>
#include <termios.h>
#include <string_view>
#include <libvirt/libvirt.h>
#include <libvirt/virterror.h>
#include <VirtXX/Impl/datatypes.hxx>
#include <VirtXX/Impl/LibvirtDomainConsole.hxx>
#include <VirtXX/Impl/LibvirtDomainCreationKey.hxx>

VirtXX::Impl::LibvirtDomainConsole::LibvirtDomainConsole([[maybe_unused]] LibvirtDomainCreationKey key, virDomainPtr domain)
  : m_StreamPtr(virStreamNew(virDomainGetConnect(domain), 0), Deleters::LibvirtStreamPtrDeleter()) {
  if (!m_StreamPtr) { /* TODO: Handle Error */ }
  if (virDomainOpenConsole(domain, nullptr, m_StreamPtr.get(), VIR_DOMAIN_CONSOLE_FORCE) < 0) { /* TODO: Handle Error */ }
}

VirtXX::Impl::LibvirtDomainConsole::~LibvirtDomainConsole() { stop(); }

bool VirtXX::Impl::LibvirtDomainConsole::is_active() const { return m_Active; }

void VirtXX::Impl::LibvirtDomainConsole::start_listening(OutputCallback on_output) {
  if (m_Active) return;
  m_Active = true;

  m_ReaderThread = std::thread([this, on_output]() {
    std::vector<char> buffer(1024);
    while (m_Active) {
      int bytes_read = virStreamRecv(m_StreamPtr.get(), buffer.data(), buffer.size());
      if (bytes_read <= 0) {
        m_Active = false;
        break;
      }
      if (on_output) on_output(std::string_view(buffer.data(), bytes_read));
    }
  });
}

bool VirtXX::Impl::LibvirtDomainConsole::send_input(std::string_view data) {
  if (!m_Active || !m_StreamPtr) return false;
  
  // ASCII 29 (0x1D) is Ctrl+] to detach from the console cleanly
  if (!data.empty() && data[0] == 0x1D) {
    stop();
    return true;
  }

  return virStreamSend(m_StreamPtr.get(), data.data(), data.size()) >= 0;
}

void VirtXX::Impl::LibvirtDomainConsole::stop() {
  if (!m_Active) return;
  m_Active = false;
  if (m_StreamPtr) virStreamAbort(m_StreamPtr.get()); 
  if (m_ReaderThread.joinable()) m_ReaderThread.join();
}

