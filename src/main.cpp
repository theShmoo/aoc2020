#include "days.hpp"

static constexpr days::day current_day = days::day::day_3;

auto main([[maybe_unused]] int argc, [[maybe_unused]] const char **argv) -> int
{
  spdlog::info("Advent of Code 2020");

  days::solve_problem<days::day::day_1, days::part::part_1>();
  days::solve_problem<days::day::day_1, days::part::part_2>();
  days::solve_problem<days::day::day_2, days::part::part_1>();
  days::solve_problem<days::day::day_2, days::part::part_2>();
  days::solve_problem<current_day, days::part::part_1>();
  days::solve_problem<current_day, days::part::part_2>();
}
