#include "days.hpp"
#include "input_utils.hpp"

#include <range/v3/all.hpp>

static constexpr char empty_seat = 'L';
static constexpr char floor_seat = '.';
static constexpr char occupied_seat = '#';
using seats = std::vector<std::string>;

auto count_seats_adjacent_1(seats const &seats,
  int const row,
  int const col,
  char const to_count) -> int
{
  auto num = 0;
  auto const max_col = static_cast<int>(seats.front().size());
  auto const max_row = static_cast<int>(seats.size());
  for (auto c = col - 1; c <= col + 1; ++c) {
    for (auto r = row - 1; r <= row + 1; ++r) {
      if (
        // not the seat itself
        (c != col || r != row)
        // x boundary check
        && c < max_col
        && c >= 0
        // y boundary check
        && r < max_row && r >= 0)
        num += seats[r][c] == to_count;
    }
  }
  return num;
}

auto count_seats_adjacent_2(seats const &seats,
  int const row,
  int const col,
  char const to_count) -> int
{
  auto num = 0;
  auto const max_col = static_cast<int>(seats.front().size());
  auto const max_row = static_cast<int>(seats.size());
  for (auto x = -1; x <= 1; ++x) {
    for (auto y = -1; y <= 1; ++y) {
      if (x != 0 || y != 0) {
        auto found = false;
        auto c = col + y;
        auto r = row + x;
        while (!found && c < max_col && c >= 0
               && r < max_row && r >= 0) {
          if (seats[r][c] == empty_seat) break;
          found = seats[r][c] == to_count;
          c += y;
          r += x;
        }
        num += found;
      }
    }
  }
  return num;
}

template<int Tolerance>
auto get_next_seats(seats const &last, auto &&count_predicate) -> seats
{
  auto next = last;
  for (auto &&[row, line] : last | ranges::views::enumerate) {
    for (auto &&[col, c] : line | ranges::views::enumerate) {
      switch (c) {
      case empty_seat: {
        auto const n = count_predicate(last, row, col, occupied_seat);
        if (n == 0) next[row][col] = occupied_seat;
        break;
      }
      case occupied_seat: {
        auto const n = count_predicate(last, row, col, occupied_seat);
        if (n >= Tolerance) next[row][col] = empty_seat;
        break;
      }
      case floor_seat:
      default:
        break;
      }
    }
  }
  return next;
}

auto count_occupied(seats const &seats) -> size_t
{
  return ranges::accumulate(seats, 0, [](size_t sum, auto const &line) {
    return sum + ranges::count(line, occupied_seat);
  });
}

template<>
auto days::solve<days::day::day_11, days::part::part_1>(std::istream &input)
  -> std::string
{
  auto seats{ utils::split<std::string>(input) };
  auto next_seats = get_next_seats<4>(seats, count_seats_adjacent_1);
  while (next_seats != seats) {
    seats = next_seats;
    next_seats = get_next_seats<4>(seats, count_seats_adjacent_1);
  }
  return std::to_string(count_occupied(seats));
}


template<>
auto days::solve<days::day::day_11, days::part::part_2>(std::istream &input)
  -> std::string
{
  auto seats{ utils::split<std::string>(input) };
  auto next_seats = get_next_seats<5>(seats, count_seats_adjacent_2);
  while (next_seats != seats) {
    seats = next_seats;
    next_seats = get_next_seats<5>(seats, count_seats_adjacent_2);
  }
  return std::to_string(count_occupied(seats));
}
