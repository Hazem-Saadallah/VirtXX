#include <datatypes.hxx>
#include <ErrorBlock.hxx>

_ErrorBlock::_ErrorBlock(_datatype::ErrorCode_t code, const _datatype::ErrorMsg_t& message) : m_Code(code), m_Message(message) { }

_datatype::ErrorCode_t _ErrorBlock::code() const { return m_Code; }
_datatype::ErrorMsg_t _ErrorBlock::message() const { return m_Message; }
