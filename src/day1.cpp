#include "days.hpp"
#include "combination_utils.hpp"

#include <vector>
#include <range/v3/all.hpp>
#include <span>

void solveDay(unsigned int const comb_size,
  std::istream &input,
  std::ostream &output)
{
  auto expanses = ranges::istream_view<int>(input) | ranges::to<std::vector>();
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
  output << ranges::accumulate(result, 1, std::multiplies<int>{}) << "\n";
}

template<>
void days::solve<days::Day::Day1, days::Part::Part1>(std::istream &input,
  std::ostream &output)
{
  solveDay(2, input, output);
}

template<>
void days::solve<days::Day::Day1, days::Part::Part2>(std::istream &input,
  std::ostream &output)
{
  solveDay(3, input, output);
}
