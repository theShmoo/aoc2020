#include "days.hpp"
#include "combination_utils.hpp"
#include "input_utils.hpp"

#include <vector>
#include <range/v3/all.hpp>
#include <span>


auto solve_day(unsigned int const comb_size, std::istream &input) -> int
{
  auto expanses = utils::split<int>(input);
  ranges::sort(expanses);
  auto lazyCombo = [expanses, comb_size]() mutable {
    utils::next_combination(
      expanses.begin(), expanses.begin() + comb_size, expanses.end());
    return std::span(expanses.begin(), expanses.begin() + comb_size);
  };
  auto combinations = ranges::views::generate(lazyCombo);
  auto found = ranges::find_if(combinations,
    [](auto const &comb) { return ranges::accumulate(comb, 0) == 2020; });
  auto const result = *found;
  return ranges::accumulate(result, 1, std::multiplies<int>{});
}

template<>
auto days::solve<days::day::day_1, days::part::part_1>(std::istream &input)
  -> std::string
{
  return std::to_string(solve_day(2, input));
}

template<>
auto days::solve<days::day::day_1, days::part::part_2>(std::istream &input)
  -> std::string
{
  return std::to_string(solve_day(3, input));
}
