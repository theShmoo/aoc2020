#include "days.hpp"

#include <range/v3/all.hpp>
#include <map>
#include <numeric>

struct code
{
  int row;
  int col;
};

std::vector<code> parse_codes(std::istream &input)
{
  return ranges::istream_view<std::string>(input)
         | ranges::views::transform([](auto const line) {
             code code;
             code.row = ranges::accumulate(line.substr(0, 7),
               0,
               [power = 6](auto const sum, auto const c) mutable {
                 auto const seats = 1 << power--;
                 if (c == 'F') return sum;
                 return seats + sum;
               });
             code.col = ranges::accumulate(line.substr(7, 3),
               0,
               [power = 2](auto const sum, auto const c) mutable {
                 auto const seats = 1 << power--;
                 if (c == 'L') return sum;
                 return seats + sum;
               });
             return code;
           })
         | ranges::to<std::vector>();
}

auto to_id(code const c) -> int { return c.row * 8 + c.col; }

template<>
auto days::solve<days::day::day_5, days::part::part_1>(std::istream &input)
  -> std::string
{
  auto const codes = parse_codes(input);
  const auto highest_id = ranges::max(codes | ranges::views::transform(to_id));
  return std::to_string(highest_id);
}

template<>
auto days::solve<days::day::day_5, days::part::part_2>(std::istream &input)
  -> std::string
{
  auto const codes = parse_codes(input);
  auto code_ids =
    codes | ranges::views::transform(to_id) | ranges::to<std::vector>;
  ranges::sort(code_ids);
  std::vector<int> diffs(code_ids.size());
  std::adjacent_difference(code_ids.begin(), code_ids.end(), diffs.begin());
  auto const found = ranges::find(diffs, 2);
  auto const d = std::distance(diffs.begin(), found);
  return std::to_string(code_ids[d-1] + 1);
}
