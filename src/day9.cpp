#include "days.hpp"
#include "day9.hpp"

#include <range/v3/all.hpp>
#include <deque>

template<>
auto days::solve<days::day::day_9, days::part::part_1>(std::istream &input)
  -> std::string
{
  return preamble_finder<25>::solve_part1(input);
}

template<>
auto days::solve<days::day::day_9, days::part::part_2>(std::istream &input)
  -> std::string
{
  return preamble_finder<25>::solve_part2(input);
}