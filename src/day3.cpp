#include "days.hpp"

#include <range/v3/all.hpp>

struct t
{
};

std::vector<t> parse_day(std::istream &input)
{
  std::vector<t> result;

  auto const r = std::regex("([0-9]+)-([0-9]+) ([a-z]): ([a-z]+)");
  std::smatch m;
  for (std::string line; std::getline(input, line);) {
    std::regex_match(line, m, r);
  }
  return result;
}

template<>
auto days::solve<days::day::day_3, days::part::part_1>(std::istream &input)
  -> std::string
{
  auto parsed = parse_day(input);
  return {};
}

template<>
auto days::solve<days::day::day_3, days::part::part_2>(std::istream &input)
  -> std::string
{
  auto parsed = parse_day(input);
  return {};
}
