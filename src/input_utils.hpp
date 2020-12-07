#pragma once

#include <string>
#include <vector>
#include <istream>
#include <range/v3/all.hpp>

namespace utils {

auto split(std::istream &input, char delimiter) -> std::vector<std::string>;

template<typename T = std::string>
auto split(std::istream &input) -> std::vector<T>
{
  return ranges::istream_view<T>(input) | ranges::to<std::vector>();
}

template<typename UnaryFun>
void for_each_input(std::istream &input, const char delimiter, UnaryFun &&fun)
{
  std::string token;
  while (std::getline(input, token, delimiter)) { fun(token); }
}
}// namespace utils
