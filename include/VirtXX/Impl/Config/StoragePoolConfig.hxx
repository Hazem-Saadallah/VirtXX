#pragma once

#include "VirtXX/Impl/Config/Datatype.hxx"
#include <cstdint>
#include <unordered_map>
#include <variant>
#include <filesystem>
#include <VirtXX/Impl/Misc.hxx>
#include <VirtXX/Impl/Config/ConfigValue.hxx>
#include <VirtXX/Impl/Config/Base/BaseConfig.hxx>

namespace VirtXX {
  namespace Config {
    namespace Impl {
      class StoragePoolConfig : public BaseConfig {
      public:
        enum class Field : std::uint8_t { NAME, TYPE, TARGET_PATH, };

      private:
        std::unordered_map<StoragePoolConfig::Field, std::variant<ConfigValue<std::string>>> m_Values = {
          {StoragePoolConfig::Field::TYPE, ConfigValue<std::string>({"pool", "@type"}, Config::Impl::Datatype::get_storage_pool_type_string(Config::Impl::Datatype::StoragePoolType::DIRECTORY))},
          {StoragePoolConfig::Field::NAME, ConfigValue<std::string>({"pool", "name"}, VirtXX::Impl::Misc::generate_random_string(10, "VirtXX_POOL_", ""))},
          {StoragePoolConfig::Field::TARGET_PATH ,ConfigValue<std::string>({"pool", "target", "path"}, std::filesystem::current_path().string())},
        };

      public:
        StoragePoolConfig();
        ~StoragePoolConfig() = default;
        StoragePoolConfig(StoragePoolConfig&& other) noexcept = default;
        StoragePoolConfig &operator=(StoragePoolConfig&& other) noexcept = delete;
        StoragePoolConfig(const StoragePoolConfig& ) = delete;
        StoragePoolConfig &operator=(const StoragePoolConfig& ) = delete;
        
      public:
        std::string get_type();
        void set_type(Config::Impl::Datatype::StoragePoolType type);

        std::string get_name();
        void set_name(const std::string& name);

        std::string get_target_path();
        void set_target_path(const std::string& target_path);
      };
    }
  }
}
