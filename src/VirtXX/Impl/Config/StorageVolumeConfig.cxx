#include <VirtXX/Impl/Config/Datatype.hxx>
#include <VirtXX/Impl/Config/StorageVolumeConfig.hxx>

VirtXX::Impl::Config::StorageVolumeConfig::StorageVolumeConfig() : BaseConfig() {
  set_value_map({
    {static_cast<std::uint8_t>(StorageVolumeConfig::Field::TYPE), Datatype::ValueString(m_Document, {"volume", "@type"}, Datatype::get_storage_volume_type_string(Datatype::StorageVolumeType::FILE))},
    {static_cast<std::uint8_t>(StorageVolumeConfig::Field::NAME), Datatype::ValueString(m_Document, {"volume", "name"}, VirtXX::Impl::Misc::generate_random_string(10, "VirtXX_VOLUME_", ""))},
    {static_cast<std::uint8_t>(StorageVolumeConfig::Field::CAPACITY), Datatype::ValueString(m_Document, {"volume","capacity"}, 0)},
    {static_cast<std::uint8_t>(StorageVolumeConfig::Field::CAPACITY_UNIT), Datatype::ValueString(m_Document, {"volume", "capacity", "@unit"}, Datatype::get_storage_unit_string(Datatype::StorageUnit::BYTES))},
    {static_cast<std::uint8_t>(StorageVolumeConfig::Field::ALLOCATION), Datatype::ValueUInt64(m_Document, {"volume", "allocation"}, 0)},
    {static_cast<std::uint8_t>(StorageVolumeConfig::Field::ALLOCATION_UNIT), Datatype::ValueString(m_Document, {"volume", "allocation", "@unit"}, Datatype::get_storage_unit_string(Datatype::StorageUnit::BYTES))},
    {static_cast<std::uint8_t>(StorageVolumeConfig::Field::TARGET_FORMAT_TYPE), Datatype::ValueString(m_Document, {"volume", "target", "format", "@type"}, Datatype::get_file_format_type_string(Datatype::FileFormatType::RAW))}
  });
}


std::string VirtXX::Impl::Config::StorageVolumeConfig::get_type() { return std::get<Datatype::ValueString>(m_Values.at(static_cast<std::uint8_t>(Field::TYPE))).get_value_or_default(); }
void VirtXX::Impl::Config::StorageVolumeConfig::set_type(VirtXX::Impl::Config::Datatype::StorageVolumeType type) {
  std::get<Datatype::ValueString>((m_Values.at(static_cast<std::uint8_t>(Field::TYPE)))).set_value(Datatype::get_storage_volume_type_string(type));
}

std::string VirtXX::Impl::Config::StorageVolumeConfig::get_name() { return std::get<Datatype::ValueString>(m_Values.at(static_cast<std::uint8_t>(Field::NAME))).get_value_or_default(); }
void VirtXX::Impl::Config::StorageVolumeConfig::set_name(const std::string& name) { std::get<Datatype::ValueString>((m_Values.at(static_cast<std::uint8_t>(Field::NAME)))).set_value(name); }

std::uint64_t VirtXX::Impl::Config::StorageVolumeConfig::get_capacity() { return std::get<Datatype::ValueUInt64>(m_Values.at(static_cast<std::uint8_t>(Field::CAPACITY))).get_value_or_default(); }
void VirtXX::Impl::Config::StorageVolumeConfig::set_capacity(std::uint64_t capacity) { std::get<Datatype::ValueUInt64>((m_Values.at(static_cast<std::uint8_t>(Field::CAPACITY)))).set_value(capacity); }

std::string VirtXX::Impl::Config::StorageVolumeConfig::get_capacity_unit() { return std::get<Datatype::ValueString>(m_Values.at(static_cast<std::uint8_t>(Field::CAPACITY_UNIT))).get_value_or_default(); }
void VirtXX::Impl::Config::StorageVolumeConfig::set_capacity_unit(VirtXX::Impl::Config::Datatype::StorageUnit unit) {
  std::get<Datatype::ValueString>((m_Values.at(static_cast<std::uint8_t>(Field::CAPACITY_UNIT)))).set_value(VirtXX::Impl::Config::Datatype::get_storage_unit_string(unit));
}

std::uint64_t VirtXX::Impl::Config::StorageVolumeConfig::get_allocation() { return std::get<Datatype::ValueUInt64>(m_Values.at(static_cast<std::uint8_t>(Field::ALLOCATION))).get_value_or_default(); }
void VirtXX::Impl::Config::StorageVolumeConfig::set_allocation(std::uint64_t allocation) { std::get<Datatype::ValueUInt64>((m_Values.at(static_cast<std::uint8_t>(Field::ALLOCATION)))).set_value(allocation); }

std::string VirtXX::Impl::Config::StorageVolumeConfig::get_allocation_unit() { return std::get<Datatype::ValueString>(m_Values.at(static_cast<std::uint8_t>(Field::ALLOCATION))).get_value_or_default(); }
void VirtXX::Impl::Config::StorageVolumeConfig::set_allocation_unit(VirtXX::Impl::Config::Datatype::StorageUnit unit) {
  std::get<Datatype::ValueString>((m_Values.at(static_cast<std::uint8_t>(Field::ALLOCATION_UNIT)))).set_value(VirtXX::Impl::Config::Datatype::get_storage_unit_string(unit));
}

std::string VirtXX::Impl::Config::StorageVolumeConfig::get_file_format_type() { return std::get<Datatype::ValueString>(m_Values.at(static_cast<std::uint8_t>(Field::TARGET_FORMAT_TYPE))).get_value_or_default(); }
void VirtXX::Impl::Config::StorageVolumeConfig::set_file_format_type(VirtXX::Impl::Config::Datatype::FileFormatType format_type) {
  std::get<Datatype::ValueString>((m_Values.at(static_cast<std::uint8_t>(Field::TARGET_FORMAT_TYPE)))).set_value(VirtXX::Impl::Config::Datatype::get_file_format_type_string(format_type));
}
