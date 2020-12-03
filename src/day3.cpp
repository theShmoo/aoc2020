#include "days.hpp"

#include <range/v3/all.hpp>

struct slope
{
  unsigned int col;
  unsigned int row;
};

auto num_trees_in_slope(const slope slope,
  const std::vector<std::string> &lines) -> unsigned int
{
  unsigned int trees = 0;
  unsigned int col = 0;
  for (unsigned int row = 0; row < lines.size(); row += slope.row) {
    auto const &line = lines[row];
    auto const l = line.at(col % line.size());
    if (l == '#') trees++;
    col += slope.col;
  }
  return trees;
}

template<>
auto days::solve<days::day::day_3, days::part::part_1>(std::istream &input)
  -> std::string
{
  auto lines =
    ranges::istream_view<std::string>(input) | ranges::to<std::vector>();
  auto const trees = num_trees_in_slope({ 3, 1 }, lines);
  return std::to_string(trees);
}

template<>
auto days::solve<days::day::day_3, days::part::part_2>(std::istream &input)
  -> std::string
{
  auto lines =
    ranges::istream_view<std::string>(input) | ranges::to<std::vector>();

  std::array<slope, 5> slopes{
    slope{ 1, 1 }, slope{ 3, 1 }, slope{ 5, 1 }, slope{ 7, 1 }, slope{ 1, 2 }
  };
  auto const result = ranges::accumulate(
    slopes | ranges::views::transform([&lines](auto const slope) {
      return num_trees_in_slope(slope, lines);
    }),
    1,
    std::multiplies<>{});

  return std::to_string(result);
}
