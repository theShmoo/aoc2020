#include <map>

#include "days.hpp"
#include "input_utils.hpp"

#include <range/v3/all.hpp>


template<>
auto days::solve<days::day::day_10, days::part::part_1>(std::istream &input)
  -> std::string
{
  auto adapters_sorted = utils::split<int>(input);
  ranges::sort(adapters_sorted);
  adapters_sorted.push_back(adapters_sorted.back() + 3);
  std::vector<int> diffs(adapters_sorted.size());
  ranges::adjacent_difference(adapters_sorted, diffs.begin());
  auto const ones = ranges::count(diffs, 1);
  auto const threes = ranges::count(diffs, 3);
  return std::to_string(ones * threes);
}

template<>
auto days::solve<days::day::day_10, days::part::part_2>(std::istream &input)
  -> std::string
{
  auto adapters_sorted = utils::split<int>(input);
  ranges::sort(adapters_sorted);
  // but adding the zero charge is needed
  adapters_sorted.insert(adapters_sorted.begin(), 0);
  adapters_sorted.push_back(adapters_sorted.back() + 3);
  auto current = adapters_sorted.begin();
  const auto end = adapters_sorted.end();
  size_t combinations = 1u;
  while (current != end)
  {
    auto const next = std::adjacent_find(
      current, end, [](const int l, const int r)
      {
        return r - l > 1;
      });
    auto const num_adjacent = std::distance(current, next) + 1;
    if (num_adjacent == 3) {
      combinations *= 2;
    } else if (num_adjacent == 4) {
      combinations *= 4;
    } else if (num_adjacent == 5) {
      combinations *= 7;
    } else if (num_adjacent > 5) {
      spdlog::error("not yet considered {}", num_adjacent);
    }
    current = next;
    if (current != end) {
      ++current;
    }
  }
  
  return std::to_string(combinations);
}
