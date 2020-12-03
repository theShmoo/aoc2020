#include <sstream>
#include <catch2/catch.hpp>

#include "days.hpp"


TEST_CASE("Day 1 Part 1", "[days]")
{
  std::stringstream ss{"1721\n979\n366\n299\n675\n1456"};
  auto const out = days::solve<days::day::day_1, days::part::part_1>(ss);
  REQUIRE(out == "514579");
}

TEST_CASE("Day 1 Part 2", "[days]")
{
  std::stringstream ss{ "1721\n979\n366\n299\n675\n1456" };
  auto const out = days::solve<days::day::day_1, days::part::part_2>(ss);
  REQUIRE(out == "241861950");
}

TEST_CASE("Day 2 Part 1", "[days]")
{
  std::stringstream ss{ "1-3 a: abcde\n1-3 b: cdefg\n2-9 c: ccccccccc" };
  auto const out = days::solve<days::day::day_2, days::part::part_1>(ss);
  REQUIRE(out == "2");
}

TEST_CASE("Day 2 Part 2", "[days]")
{
  std::stringstream ss{ "1-3 a: abcde\n1-3 b: cdefg\n2-9 c: ccccccccc" };
  auto const out = days::solve<days::day::day_2, days::part::part_2>(ss);
  REQUIRE(out == "1");
}

TEST_CASE("Day 3 Part 1", "[days]")
{
  std::stringstream ss{
    "..##.......\n#...#...#..\n.#....#..#.\n..#.#...#.#\n.#...##..#.\n..#.##..."
    "..\n.#.#.#....#\n.#........#\n#.##...#...\n#...##....#\n.#..#...#.#"
  };
  auto const out = days::solve<days::day::day_3, days::part::part_1>(ss);
  REQUIRE(out == "7");
}

TEST_CASE("Day 3 Part 2", "[days]")
{
  std::stringstream ss{
    "..##.......\n#...#...#..\n.#....#..#.\n..#.#...#.#\n.#...##..#.\n..#.##..."
    "..\n.#.#.#....#\n.#........#\n#.##...#...\n#...##....#\n.#..#...#.#"
  };
  auto const out = days::solve<days::day::day_3, days::part::part_2>(ss);
  std::cout << out;
  REQUIRE(out == "336");
}