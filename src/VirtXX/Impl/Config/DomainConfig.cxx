#include <VirtXX/Impl/Misc.hxx>
#include <VirtXX/Impl/Config/Datatype.hxx>
#include <VirtXX/Impl/Config/DomainConfig.hxx>
#include <VirtXX/Impl/Config/Base/BaseConfig.hxx>
#include <VirtXX/Impl/Config/Value.hxx>

VirtXX::Impl::Config::DomainConfig::DomainConfig() : BaseConfig() {
  set_value_map({
    {static_cast<std::uint8_t>(DomainConfig::Field::TYPE), Datatype::ValueString(m_Document, {"domain", "@type"}, Datatype::get_domain_type_string(Datatype::DomainType::KVM))},
    {static_cast<std::uint8_t>(DomainConfig::Field::NAME), Datatype::ValueString(m_Document, {"domain", "name"}, VirtXX::Impl::Misc::generate_random_string(10, "VirtXX_DOMAIN_", ""))},
    {static_cast<std::uint8_t>(DomainConfig::Field::MEMORY), Datatype::ValueUInt64(m_Document, {"domain", "memory"}, 0)},
    {static_cast<std::uint8_t>(DomainConfig::Field::MEMORY_UNIT), Datatype::ValueString(m_Document, {"domain", "memory", "@unit"}, Datatype::get_storage_unit_string(Datatype::StorageUnit::KIB))},
    {static_cast<std::uint8_t>(DomainConfig::Field::VCPU), Datatype::ValueUInt64(m_Document, {"domain", "vcpu"}, 0)},
  });
}

std::string VirtXX::Impl::Config::DomainConfig::get_type() { return std::get<Datatype::ValueString>(m_Values.at(static_cast<std::uint8_t>(DomainConfig::Field::TYPE))).get_value_or_default(); }
void VirtXX::Impl::Config::DomainConfig::set_type(Datatype::DomainType domain_type) { std::get<Datatype::ValueString>(m_Values.at(static_cast<std::uint8_t>(DomainConfig::Field::TYPE))).set_value(Datatype::get_domain_type_string(domain_type)); }

std::string VirtXX::Impl::Config::DomainConfig::get_name() { return std::get<Datatype::ValueString>(m_Values.at(static_cast<std::uint8_t>(DomainConfig::Field::NAME))).get_value_or_default(); }
void VirtXX::Impl::Config::DomainConfig::set_name(const std::string& name) { std::get<Datatype::ValueString>(m_Values.at(static_cast<std::uint8_t>(DomainConfig::Field::NAME))).set_value(name); }

std::uint64_t VirtXX::Impl::Config::DomainConfig::get_memory() { return std::get<Datatype::ValueUInt64>(m_Values.at(static_cast<std::uint8_t>(DomainConfig::Field::MEMORY))).get_value_or_default(); }
void VirtXX::Impl::Config::DomainConfig::set_memory(std::uint64_t memory) { std::get<Datatype::ValueUInt64>(m_Values.at(static_cast<std::uint8_t>(DomainConfig::Field::MEMORY))).set_value(memory); }

std::string VirtXX::Impl::Config::DomainConfig::get_memory_unit() { return std::get<Datatype::ValueString>(m_Values.at(static_cast<std::uint8_t>(DomainConfig::Field::MEMORY_UNIT))).get_value_or_default(); }
void VirtXX::Impl::Config::DomainConfig::set_memory_unit(Datatype::StorageUnit storage_unit) {
  std::get<Datatype::ValueString>(m_Values.at(static_cast<std::uint8_t>(DomainConfig::Field::MEMORY_UNIT))).set_value(Datatype::get_storage_unit_string(storage_unit));
}

std::uint64_t VirtXX::Impl::Config::DomainConfig::get_vcpu() { return std::get<Datatype::ValueUInt64>(m_Values.at(static_cast<std::uint8_t>(DomainConfig::Field::VCPU))).get_value_or_default(); }
void VirtXX::Impl::Config::DomainConfig::set_vcpu(std::uint64_t vcpu) { std::get<Datatype::ValueUInt64>(m_Values.at(static_cast<std::uint8_t>(DomainConfig::Field::VCPU))).set_value(vcpu); }
