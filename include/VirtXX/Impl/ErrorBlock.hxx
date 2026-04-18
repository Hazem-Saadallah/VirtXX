#pragma once

#include <VirtXX/Impl/datatypes.hxx>

namespace VirtXX {
  namespace Impl {
    class ErrorBlock {
    private:
      datatype::ErrorCode m_Code = datatype::ErrorCode::NONE;
      datatype::ErrorMsg m_Message = std::string();

    public:
      ErrorBlock() = default;
      ErrorBlock(datatype::ErrorCode code, const datatype::ErrorMsg& message);
      ~ErrorBlock() = default;
      ErrorBlock(const ErrorBlock &) = default;
      ErrorBlock &operator=(ErrorBlock &&) = default;
      ErrorBlock(ErrorBlock &&) = default;
      ErrorBlock &operator=(const ErrorBlock &) = default;

      datatype::ErrorCode code() const;
      datatype::ErrorMsg message() const;
    };
  }
}
