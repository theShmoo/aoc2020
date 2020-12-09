#include <deque>

#include "days.hpp"

#include <range/v3/all.hpp>

#include "input_utils.hpp"

static constexpr size_t preamble_size = 25;
using preamble = std::array<int, preamble_size>;

auto find_pair(preamble &p, size_t &current_pos, const int num) -> bool
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
  current_pos = (current_pos + 1) % preamble_size;
  return false;
}

auto find_wrong_number(std::vector<int> const &numbers) -> auto
{
  preamble preamble{};
  std::copy_n(numbers.begin(), preamble_size, preamble.begin());
  size_t current_pos = 0;
  auto const found = std::find_if(numbers.begin() + preamble_size,
    numbers.end(),
    [&preamble, &current_pos](
      const int value) { return find_pair(preamble, current_pos, value); });
  return found;
}

template<>
auto days::solve<days::day::day_9, days::part::part_1>(std::istream &input)
  -> std::string
{
  auto const numbers = utils::split<int>(input);
  auto const found = find_wrong_number(numbers);
  return std::to_string(*found);
}

template<>
auto days::solve<days::day::day_9, days::part::part_2>(std::istream &input)
  -> std::string
{
  auto const numbers = utils::split<int>(input);
  auto const found = *find_wrong_number(numbers);

  std::deque<int> range{};
  auto sum = 0;
  auto range_end = std::find_if(begin(numbers),
    end(numbers),
    [found, &sum, &range](auto const num) {
      sum += num;
      range.push_back(num);
      if (found == sum) { return true; }
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
