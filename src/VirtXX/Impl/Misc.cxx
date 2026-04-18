#include <string>
#include <format>
#include <random>
#include <VirtXX/Impl/Misc.hxx>

std::string VirtXX::Impl::Misc::generate_random_string(std::size_t length, std::string prefix, std::string suffix) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<std::int32_t> dist(1, 9);
  std::string rand_str;
  rand_str.reserve(length);
  for(std::size_t i{0}; i < length; ++i) rand_str.append(std::to_string(dist(gen)));
  return std::format("{}{}{}", prefix, rand_str, suffix);
}

