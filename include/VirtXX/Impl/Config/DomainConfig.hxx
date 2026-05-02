#pragma once

#include <cstdint>
#include <string>
#include <VirtXX/Impl/Config/Datatype.hxx>
#include <VirtXX/Impl/Config/Base/BaseConfig.hxx>
#include <VirtXX/Impl/Config/Value.hxx>

namespace VirtXX {
namespace Impl{
namespace Config {
class DomainConfig : public BaseConfig {
public:
  enum class Field : std::uint8_t { TYPE, NAME, MEMORY, MEMORY_UNIT, VCPU, };


public:
  DomainConfig();
  ~DomainConfig() = default;
  DomainConfig(DomainConfig&& other) noexcept = default;
  DomainConfig &operator=(DomainConfig&& other) noexcept = default;
  DomainConfig(const DomainConfig& other) = default;
  DomainConfig &operator=(const DomainConfig& other) = default;

public:
  std::string get_type();
  void set_type(Datatype::DomainType domain_type);

  std::string get_name();
  void set_name(const std::string& name);

  std::uint64_t get_memory();
  void set_memory(std::uint64_t memory);

  std::string get_memory_unit();
  void set_memory_unit(Datatype::StorageUnit storage_unit);

  std::uint64_t get_vcpu();
  void set_vcpu(std::uint64_t vcpu);
};
} /* Impli  */
} /* Config */
} /* VirtXX */
