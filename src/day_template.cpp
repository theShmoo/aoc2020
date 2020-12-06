/*
#include "days.hpp"

#include <range/v3/all.hpp>

using groups = std::vector<std::string>;

auto parse_input(std::istream &input) -> groups
{
  groups groups =
    ranges::istream_view<std::string>(input) | ranges::to<std::vector>();
  return groups;
}

template<>
auto days::solve<days::day::day_err, days::part::part_1>(std::istream &input)
  -> std::string
{
  auto const groups = parse_input(input);
  return std::to_string(groups.size());
}

template<>
auto days::solve<days::day::day_err, days::part::part_2>(std::istream &input)
  -> std::string
{
  auto const groups = parse_input(input);
  return std::to_string(groups.size());
}
*/