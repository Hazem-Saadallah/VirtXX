#include <VirtXX/Impl/datatypes.hxx>
#include <VirtXX/Impl/ErrorBlock.hxx>

VirtXX::Impl::_ErrorBlock::_ErrorBlock(_datatype::ErrorCode_t code, const _datatype::ErrorMsg_t& message) : m_Code(code), m_Message(message) { }
VirtXX::Impl::_datatype::ErrorCode_t VirtXX::Impl::_ErrorBlock::code() const { return m_Code; }
VirtXX::Impl::_datatype::ErrorMsg_t VirtXX::Impl::_ErrorBlock::message() const { return m_Message; }
