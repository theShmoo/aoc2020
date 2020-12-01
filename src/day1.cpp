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
    [size = expanses.size(), index = std::tuple{ 0u, 0u }]() mutable {
      auto [x, y] = index;
      if (y + 1 == size)
        index = { x + 1, 0 };
      else
        index = { x, y + 1 };
      return index;
    });

  auto combinations =
    combinationIdx | ranges::views::transform([&expanses](auto const index) {
      return std::tuple{ expanses[std::get<0>(index)],
        expanses[std::get<1>(index)] };
    });
  auto found = ranges::find_if(combinations, [](auto const &comb) {
    return std::get<0>(comb) + std::get<1>(comb) == 2020;
  });
  auto const result = *found;
  output << std::get<0>(result) << " * " << std::get<1>(result) << " = "
         << std::get<0>(result) * std::get<1>(result) << '\n';
}

template<>
void days::solve<days::Day::Day1, days::Part::Part2>(
  [[maybe_unused]] std::istream &input,
  [[maybe_unused]] std::ostream &output)
{
  auto expanses = ranges::istream_view<int>(input) | ranges::to<std::vector>();
  ranges::sort(expanses);
  auto combinationIdx = ranges::views::generate(
    [size = expanses.size(), index = std::tuple{ 0u, 0u, 0u }]() mutable {
      auto [x, y, z] = index;
      if ((z + 1) == size) {
        if (y + 1 == size)
          index = { x + 1, 0, 0 };
        else
          index = { x, y + 1, 0 };
      } else {
        index = { x, y, z + 1 };
      }
      return index;
    });

  auto combinations =
    combinationIdx | ranges::views::transform([&expanses](auto const index) {
      return std::tuple{ expanses[std::get<0>(index)],
        expanses[std::get<1>(index)],
        expanses[std::get<2>(index)] };
    });
  auto found = ranges::find_if(combinations, [](auto const &comb) {
    return std::get<0>(comb) + std::get<1>(comb) + std::get<2>(comb) == 2020;
  });
  auto const result = *found;
  output << std::get<0>(result) << " * " << std::get<1>(result) << " * "
         << std::get<2>(result) << " = "
         << std::get<0>(result) * std::get<1>(result) * std::get<2>(result)
         << '\n';
}
