#pragma once

#include <string>

namespace ErrMsg {
  const std::string null_connection_ptr = "Connection handle pointer is null";
  const std::string null_domain_ptr = "Domain handle pointer is null";
  const std::string not_an_error = "Not an Error";
  const std::string libvirt_internal_error = "Libvirt innternal error. Fetch the error object using the provided interface";
  const std::string domain_start_successful = "Domain successfully started";
  const std::string domain_start_failed = "Failed to start domain";
  const std::string domain_shutdown_successful = "Domain has been shut down successfully";
  const std::string domain_shutdown_failed = "Failed to shut down domain";
}
