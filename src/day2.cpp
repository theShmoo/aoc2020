#include "days.hpp"

#include <range/v3/all.hpp>

#include "lexical_cast.hpp"

struct Policy
{
  std::string password;
  int min;
  int max;
  char letter;
};

std::vector<Policy> parseDay(std::istream &input)
{
  std::vector<Policy> policies;

  std::regex r = std::regex("([0-9]+)-([0-9]+) ([a-z]): ([a-z]+)");
  std::smatch m;
  for (std::string line; std::getline(input, line);) {
    std::regex_match(line, m, r);
    Policy p;
    p.min = utils::lexical_cast<int>(m[1].str());
    p.max = utils::lexical_cast<int>(m[2].str());
    p.letter = m[3].str().at(0);
    p.password = m[4].str();
    policies.push_back(p);
  }
  return policies;
}

template<>
void days::solve<days::Day::Day2, days::Part::Part1>(std::istream &input,
  std::ostream &output)
{
  auto policies = parseDay(input);

  auto const numOk = ranges::count_if(policies, [](const auto p) {
    auto const num = ranges::count(p.password, p.letter);
    return num >= p.min && num <= p.max;
  });

  output << numOk << "\n";
}

template<>
void days::solve<days::Day::Day2, days::Part::Part2>(std::istream &input,
  std::ostream &output)
{
  auto policies = parseDay(input);

  auto const numOk = ranges::count_if(policies, [](const auto p) {
    return (p.letter == p.password[p.min - 1]
             && p.letter != p.password[p.max - 1])
           || (p.letter != p.password[p.min - 1]
               && p.letter == p.password[p.max - 1]);
  });

  output << numOk << "\n";
}
