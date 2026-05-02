#pragma once

#include <cstdint>
#include <VirtXX/Impl/Misc.hxx>
#include <VirtXX/Impl/Config/Value.hxx>
#include <VirtXX/Impl/Config/Datatype.hxx>
#include <VirtXX/Impl/Config/Value.hxx>
#include <VirtXX/Impl/Config/Base/BaseConfig.hxx>

namespace VirtXX {
namespace Impl {
namespace Config {
  class StoragePoolConfig : public BaseConfig {
  public:
    enum class Field : std::uint8_t { NAME, TYPE, TARGET_PATH, };

  public:
    StoragePoolConfig();
    ~StoragePoolConfig() = default;
    StoragePoolConfig(StoragePoolConfig&& other) noexcept = default;
    StoragePoolConfig &operator=(StoragePoolConfig&& other) noexcept = default;
    StoragePoolConfig(const StoragePoolConfig& other) = default;
    StoragePoolConfig &operator=(const StoragePoolConfig& other) = default;
    
  public:
    std::string get_type();
    void set_type(Datatype::StoragePoolType type);

    std::string get_name();
    void set_name(const std::string& name);

    std::string get_target_path();
    void set_target_path(const std::string& target_path);
  };
} /* Config */
} /* Impl   */
} /* VirtXX */
