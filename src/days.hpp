#pragma once

#include <spdlog/spdlog.h>
#include <chrono>
#include <fstream>
#include <iostream>

namespace days {

enum class Day {
  Day1,
  Day2,
  Day3,
  Day4,
  Day5,
  Day6,
  Day7,
  Day8,
  Day9,
  Day10,
  Day11,
  Day12,
  Day13,
  Day14,
  Day15,
  Day16,
  Day17,
  Day18,
  Day19,
  Day20,
  Day21,
  Day22,
  Day23,
  Day24,
  Day25,
  Num
};
enum class Part { Part1, Part2, Num };

template<Day day, Part part> void solveProblem()
{
  auto const humanReadableDay = static_cast<unsigned int>(day) + 1u;
  auto const humanReadablePart = static_cast<unsigned int>(part) + 1u;
  spdlog::info("solving day {} part {}", humanReadableDay, humanReadablePart);

  auto const inputFileName = fmt::format("input{}.txt", humanReadableDay);
  std::ifstream rfile(inputFileName);

  if (rfile.good()) {
    using clock = std::chrono::high_resolution_clock;
    auto const start = clock::now();
    solve<day, part>(rfile, std::cout);
    auto const finish = clock::now();
    auto const microseconds =
      std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
    spdlog::info("+solved day {} part {} in {} microseconds",
      humanReadableDay,
      humanReadablePart,
      microseconds.count());
  } else {
    spdlog::error("the input file for day {} does not exist", humanReadableDay);
  }
}

template<Day day, Part part>
void solve(std::istream &input, std::ostream &output);
}// namespace days