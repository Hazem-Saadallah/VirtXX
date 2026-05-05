#pragma once

#include <string>

#define REPORT_AND_RETURN_IF_NULL_HANDLE(return_value)                                 \
  do {                                                                                 \
    if(!get_handle()) {                                                                \
      report_error(datatype::ErrorCode::NULL_DOMAIN_PTR , ErrMsg::null_domain_ptr);    \
      return return_value;                                                             \
    }                                                                                  \
  } while(false)

#define REPORT_IF_INTERNEL_ERROR(result) \
  if(static_cast<std::int32_t>(result) < 0) report_error(datatype::ErrorCode::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error)

#define REPORT_AND_RETURN_IF_INTERNEL_ERROR(result, return_value)                                   \
  do {                                                                                              \
    if(static_cast<std::int32_t>(result) < 0) {                                                     \
      report_error(datatype::ErrorCode::LIBVIRT_INTERNAL_ERROR, ErrMsg::libvirt_internal_error);    \
      return return_value;                                                                          \
    }                                                                                               \
  } while(false)

namespace VirtXX {
namespace Impl {
namespace Misc {
  std::string generate_random_string(std::size_t length, std::string prefix="", std::string suffix="");
} /* Misc */
} /* Impl */
} /* VirtXX */
