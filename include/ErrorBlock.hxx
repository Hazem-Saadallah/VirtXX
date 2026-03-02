#pragma once

#include <datatypes.hxx>

class _ErrorBlock {
private:
  _datatype::ErrorCode_t m_Code = _datatype::ErrorCode_t::NONE;
  _datatype::ErrorMsg_t m_Message = std::string();

public:
  _ErrorBlock() = default;
  _ErrorBlock(_datatype::ErrorCode_t code, const _datatype::ErrorMsg_t& message);
  ~_ErrorBlock() = default;
  _ErrorBlock(const _ErrorBlock &) = default;
  _ErrorBlock &operator=(_ErrorBlock &&) = default;
  _ErrorBlock(_ErrorBlock &&) = default;
  _ErrorBlock &operator=(const _ErrorBlock &) = default;

  _datatype::ErrorCode_t code() const;
  _datatype::ErrorMsg_t message() const;
};
