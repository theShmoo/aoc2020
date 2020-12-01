#include "days.hpp"

#include <vector>
#include <range/v3/all.hpp>

template<>
void days::solve<days::Day::Day1, days::Part::Part1>(std::istream &input,
  std::ostream &output)
{
  auto expanses = ranges::istream_view<int>(input) | ranges::to<std::vector>();
  ranges::sort(expanses);
  auto combinationIdx = ranges::views::generate(
    [size = expanses.size(), index = std::pair{ 0u, 0u }]() mutable {
      auto [x, y] = index;
      if ((y + 1) == size)
        index = { x + 1, 0 };
      else
        index = { x, y + 1 };
      return index;
    });

  auto combinations =
    combinationIdx | ranges::views::transform([&expanses](auto const index) {
      return std::pair{ expanses[index.first], expanses[index.second] };
    });
  auto found = ranges::find_if(combinations, [](auto const &comb) {
    return comb.first + comb.second == 2020;
  });
  auto const result = *found;
  output << result.first << " * " << result.second << " = "
            << result.first * result.second << '\n';
}

template<>
void days::solve<days::Day::Day1, days::Part::Part2>(
  [[maybe_unused]] std::istream &input,
  [[maybe_unused]] std::ostream &output)
{}
