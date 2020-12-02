#include "days.hpp"

#include <range/v3/all.hpp>

#include "lexical_cast.hpp"

struct policy
{
  std::string password;
  int min;
  int max;
  char letter;
};

std::vector<policy> parse_day(std::istream &input)
{
  std::vector<policy> policies;

  auto const r = std::regex("([0-9]+)-([0-9]+) ([a-z]): ([a-z]+)");
  std::smatch m;
  for (std::string line; std::getline(input, line);) {
    std::regex_match(line, m, r);
    policy p;
    p.min = utils::lexical_cast<int>(m[1].str());
    p.max = utils::lexical_cast<int>(m[2].str());
    p.letter = m[3].str().at(0);
    p.password = m[4].str();
    policies.push_back(p);
  }
  return policies;
}

template<>
auto days::solve<days::day::day_2, days::part::part_1>(std::istream &input)
  -> std::string
{
  auto policies = parse_day(input);

  auto const num_ok = ranges::count_if(policies, [](const auto p) {
    auto const num = ranges::count(p.password, p.letter);
    return num >= p.min && num <= p.max;
  });

  return std::to_string(num_ok);
}

template<>
auto days::solve<days::day::day_2, days::part::part_2>(std::istream &input)
  -> std::string
{
  auto policies = parse_day(input);

  auto const num_ok = ranges::count_if(policies, [](const auto p) {
    return (p.letter == p.password[p.min - 1]
             && p.letter != p.password[p.max - 1])
           || (p.letter != p.password[p.min - 1]
               && p.letter == p.password[p.max - 1]);
  });

  return std::to_string(num_ok);
}
