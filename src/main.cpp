#include "days.hpp"

static constexpr days::Day CurrentDay = days::Day::Day1;

int main([[maybe_unused]] int argc, [[maybe_unused]] const char **argv)
{
  spdlog::info("Hello, {}!", "World");
  days::solveProblem<CurrentDay, days::Part::Part1>();
  days::solveProblem<CurrentDay, days::Part::Part2>();
}
