#include "days.hpp"
#include "input_utils.hpp"
#include "lexical_cast.hpp"

#include <range/v3/all.hpp>


using action = char;

static constexpr action move_north = 'N';
static constexpr action move_south = 'S';
static constexpr action move_east = 'E';
static constexpr action move_west = 'W';
static constexpr action move_forward = 'F';

static constexpr action turn_left = 'L';
static constexpr action turn_right = 'R';


struct move
{
  action action;
  int value;
};

enum class direction { north, east, south, west };

direction &operator++(direction &dir)
{
  switch (dir) {
  case direction::north:
    return dir = direction::east;
  case direction::east:
    return dir = direction::south;
  case direction::south:
    return dir = direction::west;
  case direction::west:
    return dir = direction::north;
  default:
    return dir = direction::north;
  }
}


direction &operator--(direction &dir)
{
  ++dir;
  ++dir;
  return dir = ++dir;
}

struct coordinates
{
  int x;
  int y;
};

struct position
{
  coordinates coords;
  direction dir;
};

struct position_2
{
  coordinates ship;
  coordinates waypoint;
};

auto move_coords(coordinates const &coords,
  direction const dir,
  int const value) -> coordinates
{
  switch (dir) {
  case direction::north:
    return { coords.x, coords.y + value };
  case direction::east:
    return { coords.x + value, coords.y };
  case direction::south:
    return { coords.x, coords.y - value };
  case direction::west:
    return { coords.x - value, coords.y };
  default:
    spdlog::error("unknown action");
    return coords;
  }
}

auto turn_pos(direction const dir, move const move) -> direction
{
  auto new_dir = dir;
  auto const num_turns = move.value / 90;
  for (auto i = 0; i < num_turns; ++i) {
    if (move.action == turn_right) ++new_dir;
    if (move.action == turn_left) --new_dir;
  }
  return new_dir;
}

auto rotate_pos(coordinates const &coords, move const move) -> coordinates
{
  auto new_coords = coords;
  auto const num_turns = move.value / 90;
  for (auto i = 0; i < num_turns; ++i) {
    if (move.action == turn_right) new_coords = { new_coords.y, -new_coords.x };
    if (move.action == turn_left) new_coords = { -new_coords.y, new_coords.x };
  }
  return new_coords;
}

auto change_pos(position const &pos, move const move) -> position
{
  switch (move.action) {
  case move_north:
    return { move_coords(pos.coords, direction::north, move.value), pos.dir };
  case move_south:
    return { move_coords(pos.coords, direction::south, move.value), pos.dir };
  case move_east:
    return { move_coords(pos.coords, direction::east, move.value), pos.dir };
  case move_west:
    return { move_coords(pos.coords, direction::west, move.value), pos.dir };
  case move_forward:
    return { move_coords(pos.coords, pos.dir, move.value), pos.dir };
  case turn_left:
  case turn_right:
    return { pos.coords, turn_pos(pos.dir, move) };
  default:
    spdlog::error("unknown action");
    return pos;
  }
}

auto change_pos(position_2 const &pos, move const move) -> position_2
{
  switch (move.action) {
  case move_north:
    return { pos.ship,
      move_coords(pos.waypoint, direction::north, move.value) };
  case move_south:
    return { pos.ship,
      move_coords(pos.waypoint, direction::south, move.value) };
  case move_east:
    return { pos.ship, move_coords(pos.waypoint, direction::east, move.value) };
  case move_west:
    return { pos.ship, move_coords(pos.waypoint, direction::west, move.value) };
  case move_forward: {
    return { { pos.ship.x + pos.waypoint.x * move.value,
               pos.ship.y + pos.waypoint.y * move.value },
      pos.waypoint };
  }
  case turn_left:
  case turn_right:
    return { pos.ship, rotate_pos(pos.waypoint, move) };
  default:
    spdlog::error("unknown action");
    return pos;
  }
}

auto parse_moves(std::istream &input) -> std::vector<move>
{
  auto const lines = utils::split<std::string>(input);
  return lines | ranges::views::transform([](auto const &s) -> move {
    return { s[0],
      utils::lexical_cast<int>(std::string_view{ s.begin() + 1, s.end() }) };
  }) | ranges::to_vector;
}

template<>
auto days::solve<days::day::day_12, days::part::part_1>(std::istream &input)
  -> std::string
{
  auto moves = parse_moves(input);
  auto last_pos = ranges::accumulate(moves,
    position{ { 0, 0 }, direction::east },
    [](auto const &prev_pos, auto move) { return change_pos(prev_pos, move); });
  return std::to_string(
    std::abs(last_pos.coords.x) + std::abs(last_pos.coords.y));
}

template<>
auto days::solve<days::day::day_12, days::part::part_2>(std::istream &input)
  -> std::string
{
  auto moves = parse_moves(input);
  auto last_pos = ranges::accumulate(moves,
    position_2{ { 0, 0 }, { 10, 1 } },
    [](auto const &prev_pos, auto move) { return change_pos(prev_pos, move); });
  return std::to_string(std::abs(last_pos.ship.x) + std::abs(last_pos.ship.y));
}
