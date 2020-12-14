#include "days.hpp"
#include "input_utils.hpp"
#include "lexical_cast.hpp"

#include <range/v3/all.hpp>

using precision = unsigned long long int;
using memory = std::unordered_map<precision, precision>;

struct mask
{
  precision unset;
  precision set;
  precision floating;
};

template<char C> auto find_char_in_mask(std::string_view mask_view) -> precision
{
  return ranges::accumulate(mask_view | ranges::views::reverse,
    0ULL,
    [position = 0ULL](precision sum, const char bit) mutable {
      if (bit == C) { sum += 1ULL << position; }
      ++position;
      return sum;
    });
}

auto parse_mask(std::string_view mask_view) -> mask
{

  return { find_char_in_mask<'0'>(mask_view),
    find_char_in_mask<'1'>(mask_view),
    find_char_in_mask<'X'>(mask_view) };
}

auto write_val(memory &mem,
  precision const pos,
  precision const val,
  mask const current_mask)
{
  mem[pos] = (val & ~current_mask.unset) | current_mask.set;
}

auto check_bit(precision const val, char const pos) -> bool
{
  return val & (1ULL << pos);
}

auto set_bit(precision const val, char const pos) -> precision
{
  return val | (1ULL << pos);
}

auto clear_bit(precision const val, char const pos) -> precision
{
  return val & ~(1ULL << pos);
}

auto write_mem(memory &mem,
  precision const pos,
  precision const val,
  mask const current_mask)
{
  auto const modified_pos = pos | current_mask.set;
  std::vector<precision> combinations{ modified_pos };
  for (char i = 0; i < 36; ++i) {
    if (check_bit(current_mask.floating, i)) {
      std::vector<precision> to_add;
      to_add.reserve(combinations.size());
      for (auto const c : combinations) {
        if (check_bit(c, i)) {
          to_add.push_back(clear_bit(c, i));
        } else {
          to_add.push_back(set_bit(c, i));
        }
      }
      combinations.insert(combinations.end(), to_add.begin(), to_add.end());
    }
  }
  for (auto const c : combinations) {
    mem[c] = val;
  }
}

auto solve_with_fun(std::istream &input, auto &&fun) -> precision
{
  memory mem;
  mask current_mask{ 0, 0, 0 };
  std::string line;
  while (std::getline(input, line)) {
    if (line.starts_with("mask")) {
      current_mask =
        parse_mask(std::string_view{ line.begin() + 7, line.end() });
    } else {
      auto const end = line.find_last_of(']');
      auto const begin = 4;
      auto const pos = utils::lexical_cast<unsigned>(
        std::string_view{ line.begin() + begin, line.begin() + end });
      auto const val = utils::lexical_cast<unsigned>(
        std::string_view{ line.begin() + end + 4, line.end() });
      fun(mem, pos, val, current_mask);
    }
  }
  return ranges::accumulate(mem | ranges::views::values, 0ULL);
}

template<>
auto days::solve<days::day::day_14, days::part::part_1>(std::istream &input)
  -> std::string
{
  auto const sum = solve_with_fun(input, &write_val);
  return std::to_string(sum);
}

template<>
auto days::solve<days::day::day_14, days::part::part_2>(std::istream &input)
  -> std::string
{
  auto const sum = solve_with_fun(input, &write_mem);
  return std::to_string(sum);
}