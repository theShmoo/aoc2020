#include "days.hpp"

#include <range/v3/all.hpp>
#include <map>
#include <numeric>
#include <set>

using answers = std::set<char>;
using group = std::vector<answers>;
using groups = std::vector<group>;

auto parse_groups(std::istream &input) -> groups
{
  groups groups;
  group g;
  for (std::string line; std::getline(input, line);) {
    if (line.empty()) {
      groups.push_back(g);
      g = group();
      continue;
    }
    g.push_back({ line.begin(), line.end() });
  }
  groups.push_back(g);
  return groups;
}

template<>
auto days::solve<days::day::day_6, days::part::part_1>(std::istream &input)
  -> std::string
{
  auto const groups = parse_groups(input);
  auto const result =
    ranges::accumulate(groups, 0, [](size_t sum, group const &group) {
      return sum
             + ranges::accumulate(
               group, answers{}, [](answers &uni, answers const &answers) {
                 uni.insert(answers.begin(), answers.end());
                 return uni;
               }).size();
    });
  return std::to_string(result);
}

template<>
auto days::solve<days::day::day_6, days::part::part_2>(std::istream &input)
  -> std::string
{
  auto const groups = parse_groups(input);
  auto const result =
    ranges::accumulate(groups, 0, [](size_t sum, group const &group) {
      return sum
             + std::accumulate(next(begin(group)),
               end(group),
               answers{ *begin(group) },
               [](answers &&uni, answers const &ans) {
                 answers intersection;
                 ranges::set_intersection(
                   uni, ans, std::inserter(intersection, intersection.begin()));
                 return intersection;
               }).size();
    });
  return std::to_string(result);
}
