#include <sstream>
#include <catch2/catch.hpp>

#include "days.hpp"


TEST_CASE("Day 1 Part 1", "[days]")
{
  std::stringstream ss{ "1721\n979\n366\n299\n675\n1456" };
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

TEST_CASE("Day 4 Part 1", "[days]")
{
  std::stringstream ss{
    "ecl:gry pid:860033327 eyr:2020 hcl:#fffffd\nbyr:1937 iyr:2017 cid:147 "
    "hgt:183cm\n\niyr:2013 ecl:amb cid:350 eyr:2023 pid:028048884\nhcl:#cfa07d "
    "byr:1929\n\nhcl:#ae17e1 iyr:2013\neyr:2024\necl:brn pid:760753108 "
    "byr:1931\nhgt:179cm\n\nhcl:#cfa07d eyr:2025 pid:166559648\niyr:2011 "
    "ecl:brn hgt:59in"
  };
  auto const out = days::solve<days::day::day_4, days::part::part_1>(ss);
  REQUIRE(out == "2");
}

TEST_CASE("Day 4 Part 2", "[days]")
{
  std::stringstream ss1{
    "pid:087499704 hgt:74in ecl:grn iyr:2012 eyr:2030 "
    "byr:1980\nhcl:#623a2f\n\neyr:2029 ecl:blu cid:129 byr:1989\niyr:2014 "
    "pid:896056539 hcl:#a97842 hgt:165cm\n\nhcl:#888785\nhgt:164cm byr:2001 "
    "iyr:2015 cid:88\npid:545766238 ecl:hzl\neyr:2022\n\niyr:2010 hgt:158cm "
    "hcl:#b6652a ecl:blu byr:1944 eyr:2021 pid:093154719"
  };
  auto const out_right = days::solve<days::day::day_4, days::part::part_2>(ss1);
  std::cout << out_right;
  REQUIRE(out_right == "4");

  std::stringstream ss2{
    "eyr:1972 cid:100\nhcl:#18171d ecl:amb hgt:170 pid:186cm iyr:2018 "
    "byr:1926\n\niyr:2019\nhcl:#602927 eyr:1967 hgt:170cm\necl:grn "
    "pid:012533040 byr:1946\n\nhcl:dab227 iyr:2012\necl:brn hgt:182cm "
    "pid:021572410 eyr:2020 byr:1992 cid:277\n\nhgt:59cm ecl:zzz\neyr:2038 "
    "hcl:74454a iyr:2023\npid:3556412378 byr:2007"
  };
  auto const out_wrong = days::solve<days::day::day_4, days::part::part_2>(ss2);
  std::cout << out_wrong;
  REQUIRE(out_wrong == "0");
}