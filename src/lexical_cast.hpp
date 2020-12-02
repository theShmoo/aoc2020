#pragma once
#include <sstream>
#include <optional>

namespace utils {
// tries to parse the input stream as a T
template<typename T>
inline std::optional<T> try_lexical_cast(std::istream &ss)
{
  T t;
  if ((ss >> t).fail() || !(ss >> std::ws).eof()) {
    return {};
  }
  return t;
}

// tries to parse the string as a T
template<typename T>
inline std::optional<T> try_lexical_cast(std::string_view s)
{
  std::stringstream ss{ std::string(s) };
  return try_lexical_cast<T>(ss);
}

// specialization for bool to support the reading of "true" and "false"
inline std::optional<bool> try_lexical_cast(std::string_view s)
{
  auto b = try_lexical_cast<bool>(s);
  if (b) {
    return b;
  }
  std::stringstream ss{ std::string(s) };
  ss >> std::boolalpha;
  return try_lexical_cast<bool>(ss);
}

// tries to parse the input stream as a T
// throws an exception if it fails.
template<typename T>
inline T lexical_cast(std::istream &ss)
{
  auto result = try_lexical_cast<T>(ss);
  if (!result) {
    throw std::bad_cast();
  }
  return *result;
}
// tries to parse the input string as a T
// throws an exception if it fails.
template<typename T>
inline T lexical_cast(std::string_view s)
{
  auto result = try_lexical_cast<T>(s);
  if (!result) {
    throw std::bad_cast();
  }
  return *result;
}
}
