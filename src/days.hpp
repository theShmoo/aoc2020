#pragma once

#include <spdlog/spdlog.h>
#include <chrono>
#include <fstream>
#include <iostream>

namespace days {

enum class day {
  day_1 = 1,
  day_2,
  day_3,
  day_4,
  day_5,
  day_6,
  day_7,
  day_8,
  day_9,
  day_10,
  day_11,
  day_12,
  day_13,
  day_14,
  day_15,
  day_16,
  day_17,
  day_18,
  day_19,
  day_20,
  day_21,
  day_22,
  day_23,
  day_24,
  day_25,
  num
};
enum class part { part_1 = 1, part_2, num };

template<day Day, part Part>
extern auto solve(std::istream &input) -> std::string;

template<day Day, part Part> auto solve_problem() -> void
{
  spdlog::info("solving day {} part {}", Day, Part);

  auto const input_file_name = fmt::format("input{}.txt", Day);
  std::ifstream file(input_file_name);

  if (file.good()) {
    using clock = std::chrono::high_resolution_clock;
    auto const start = clock::now();
    auto const out = solve<Day, Part>(file);
    spdlog::info("Result: {}", out);
    auto const finish = clock::now();
    auto const microseconds =
      std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
    spdlog::info("+solved day {} part {} in {} microseconds",
      Day,
      Part,
      microseconds.count());
  } else {
    spdlog::error("the input file for day {} does not exist", Day);
  }
}

}// namespace days