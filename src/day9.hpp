#pragma once
#include <deque>

#include "input_utils.hpp"

#include <range/v3/all.hpp>

template<size_t PreambleSize> struct preamble_finder
{
  using preamble = std::array<int, PreambleSize>;
  static auto find_pair(preamble &p, size_t &current_pos, const int num) -> bool
  {
    auto sorted{ p };
    ranges::sort(sorted);
    auto l = std::begin(sorted);
    auto r = std::prev(std::end(sorted));
    auto found = false;
    while (l < r) {
      auto const sum = *l + *r;
      if (sum == num) {
        found = true;
        break;
      }
      if (sum < num)
        ++l;
      else
        --r;
    }
    if (!found) return true;
    p[current_pos] = num;
    current_pos = (current_pos + 1) % PreambleSize;
    return false;
  }

  static auto find_wrong_number(std::vector<int> const &numbers) -> auto
  {
    preamble preamble{};
    std::copy_n(numbers.begin(), PreambleSize, preamble.begin());
    size_t current_pos = 0;
    auto const found =
      ranges::find_if(numbers | ranges::views::drop(PreambleSize),
        [&preamble, &current_pos](
          const int value) { return find_pair(preamble, current_pos, value); });
    return found;
  }

  static auto solve_part1(std::istream &input) -> std::string
  {
    auto const numbers = utils::split<int>(input);
    auto const found = find_wrong_number(numbers);
    return std::to_string(*found);
  }

  static auto solve_part2(std::istream &input) -> std::string
  {
    auto const numbers = utils::split<int>(input);
    auto const found = *find_wrong_number(numbers);

    std::deque<int> range{};
    auto sum = 0;
    auto range_end =
      ranges::find_if(numbers, [found, &sum, &range](auto const num) {
        sum += num;
        range.push_back(num);
        while (sum > found) {
          auto const f = range.front();
          sum -= f;
          range.pop_front();
        }
        return found == sum;
      });
    const auto [min, max] = ranges::minmax_element(range);
    return std::to_string(*min + *max);
  }
};