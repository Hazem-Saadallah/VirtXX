#include <VirtXX/Impl/datatypes.hxx>
#include <VirtXX/Impl/ErrorBlock.hxx>

VirtXX::Impl::ErrorBlock::ErrorBlock(datatype::ErrorCode code, const datatype::ErrorMsg& message) : m_Code(code), m_Message(message) { }
VirtXX::Impl::datatype::ErrorCode VirtXX::Impl::ErrorBlock::code() const { return m_Code; }
VirtXX::Impl::datatype::ErrorMsg VirtXX::Impl::ErrorBlock::message() const { return m_Message; }
