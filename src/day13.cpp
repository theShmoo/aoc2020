#include "days.hpp"
#include "input_utils.hpp"
#include "lexical_cast.hpp"

#include <range/v3/all.hpp>
#include <numeric>

template<>
auto days::solve<days::day::day_13, days::part::part_1>(std::istream &input)
  -> std::string
{
  unsigned timestamp;
  input >> timestamp;
  auto tokens = utils::split(input, ',');
  auto buses = tokens | ranges::views::remove("x")
               | ranges::views::transform([](auto const str) {
                   return utils::lexical_cast<unsigned>(str);
                 })
               | ranges::to_vector;

  auto to_wait = buses | ranges::views::transform([timestamp](auto const id) {
    return id - (timestamp % id);
  }) | ranges::to_vector;
  auto const min = ranges::min_element(to_wait);
  return std::to_string(buses[std::distance(to_wait.begin(), min)] * *min);
}

template<>
auto days::solve<days::day::day_13, days::part::part_2>(std::istream &input)
  -> std::string
{
  std::string unused;
  input >> unused;
  auto line = utils::split(input, ',');
  auto numerated =
    line | ranges::views::enumerate
    | ranges::views::filter([](auto const &s) { return s.second != "x"; })
    | ranges::views::transform([](auto const &p) {
        return std::make_pair(
          p.first, utils::lexical_cast<unsigned long long>(p.second));
      })
    | ranges::to_vector;
  auto const off =
    ranges::accumulate(numerated,
      std::make_pair(1ULL, 0ULL),
      [](auto const &old, auto const &current) {
        auto const old_period = old.first;
        auto const offset = old.second;
        auto const n = current.first;
        auto const new_period = current.second;
        auto to_find = ranges::views::iota(0ULL)
                       | ranges::views::transform(
                         [&](auto y) { return old_period * y + offset; });
        auto const found = ranges::find_if(
          to_find, [&](auto y) { return ((y + n) % new_period) == 0; });
        return std::make_pair(std::lcm(old_period, new_period), *found);
      });
  return std::to_string(off.second);
}
