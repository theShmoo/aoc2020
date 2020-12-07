#include "input_utils.hpp"

auto utils::split(std::istream &input,
  const char delimiter) -> std::vector<std::string>
{
  std::vector<std::string> tokens;
  std::string token;
  while (std::getline(input, token, delimiter)) { tokens.push_back(token); }
  return tokens;
}
