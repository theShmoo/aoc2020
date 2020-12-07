#include "days.hpp"

#include <range/v3/all.hpp>
#include <map>
#include <set>

#include "input_utils.hpp"
#include "lexical_cast.hpp"

using can_contain = std::vector<std::pair<int, std::string>>;
using bags = std::map<std::string, can_contain>;

auto parse_input(std::istream &input) -> bags
{
  auto const r1 = std::regex("([a-z]+ [a-z]+) bags contain.*");
  auto const r2 = std::regex("([0-9]+) ([a-z]+ [a-z]+)");
  auto const lines = utils::split(input, '\n');
  return lines | ranges::views::transform([&r1, &r2](std::string line) {
    std::smatch m;
    std::regex_match(line, m, r1);
    std::string bag = m[1].str();

    can_contain can_contain;

    int const sub_matches[] = { 1, 2 };
    std::regex_token_iterator<std::string::iterator> a(
      line.begin(), line.end(), r2, sub_matches);
    std::regex_token_iterator<std::string::iterator> const rend;
    while (a != rend) {
      auto const num = utils::lexical_cast<int>((a++)->str());
      can_contain.emplace_back(num, (a++)->str());
    }
    return bags::value_type{ bag, can_contain };
  }) | ranges::to<std::map>;
}

auto partition_bags(bags const &to_check,
  bags &contains,
  bags &unchecked,
  const std::set<std::string> good)
{
  ranges::partition_copy(to_check,
    ranges::inserter(contains, contains.begin()),
    ranges::inserter(unchecked, unchecked.begin()),
    [&good](auto const &bag) {
      return ranges::find_if(bag.second, [&good](auto const &pair) {
        return good.find(pair.second) != good.end();
      }) != bag.second.end();
    });
}

template<>
auto days::solve<days::day::day_7, days::part::part_1>(std::istream &input)
  -> std::string
{
  auto const b = parse_input(input);
  bags contains;
  bags unchecked;
  partition_bags(b, contains, unchecked, { "shiny gold" });

  size_t last_num_found = 0;
  size_t num_found = contains.size();
  while (last_num_found != num_found) {
    last_num_found = num_found;
    auto const good = contains | ranges::views::keys | ranges::to<std::set>;
    contains = bags{};
    bags to_check;
    std::swap(to_check, unchecked);
    partition_bags(to_check, contains, unchecked, good);
    num_found += contains.size();
  }
  return std::to_string(num_found);
}

auto num_bags(bags const &bags, can_contain const &can_contain) -> size_t
{
  size_t num = 0;
  for (auto const &bag : can_contain) {
    auto const found = bags.find(bag.second);
    if (found != bags.end()) {
      num += bag.first + (bag.first * num_bags(bags, found->second));
    }
  }
  return num;
}

template<>
auto days::solve<days::day::day_7, days::part::part_2>(std::istream &input)
  -> std::string
{
  auto const bags = parse_input(input);
  auto const found = bags.find("shiny gold");
  auto const num = num_bags(bags, found->second);
  return std::to_string(num);
}
