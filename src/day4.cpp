#include "days.hpp"

#include <range/v3/all.hpp>
#include <map>

#include "lexical_cast.hpp"

enum class field {
  byr,// (Birth Year)
  iyr,// (Issue Year)
  eyr,// (Expiration Year)
  hgt,// (Height)
  hcl,// (Hair Color)
  ecl,// (Eye Color)
  pid,// (Passport ID)
  cid,// (Country ID)
  num
};

static constexpr std::array<std::string_view, static_cast<size_t>(field::num)>
  field_names{ "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid" };

using passport = std::map<field, std::string>;

std::vector<passport> parse_day(std::istream &input)
{
  std::vector<passport> passports;

  auto const r = std::regex("([a-z]{3}):([#0-9a-z]+)");
  passport p;

  for (std::string line; std::getline(input, line);) {
    if (line.empty()) {
      passports.push_back(p);
      p = passport();
      continue;
    }
    const int sub_matches[] = { 1, 2 };
    std::regex_token_iterator<std::string::iterator> a(
      line.begin(), line.end(), r, sub_matches);
    std::regex_token_iterator<std::string::iterator> rend;
    while (a != rend) {
      auto found =
        std::find(field_names.begin(), field_names.end(), (a++)->str());
      auto const f =
        static_cast<field>(std::distance(field_names.begin(), found));
      p[f] = (a++)->str();
    }
  }
  passports.push_back(p);
  return passports;
}

auto is_in_range(std::string const &s, int min, int max) -> bool
{
  if (const auto i = utils::try_lexical_cast<int>(s)) {
    if (*i >= min && *i <= max) return true;
  }
  return false;
}

template<>
auto days::solve<days::day::day_4, days::part::part_1>(std::istream &input)
  -> std::string
{
  auto const candidates = parse_day(input);
  auto const filtered =
    candidates | ranges::views::filter([](passport const c) {
      if (c.size() == static_cast<int>(field::num)
          || (c.size() == static_cast<int>(field::num) - 1
              && c.find(field::cid) == c.end())) {
                              return true;
      }
      return false;
    })
    | ranges::to<std::vector>;
  return std::to_string(filtered.size());
}

template<>
auto days::solve<days::day::day_4, days::part::part_2>(std::istream &input)
  -> std::string
{
  auto const candidates = parse_day(input);
  auto const filtered =
    candidates | ranges::views::filter([](passport const c) {
      if (c.size() == static_cast<int>(field::num)
          || (c.size() == static_cast<int>(field::num) - 1
              && c.find(field::cid) == c.end())) {
        for (size_t n = 0; n < static_cast<size_t>(field::num); ++n) {
          auto const f = static_cast<field>(n);
          if (f == field::cid) continue;
          auto const s = c.find(f)->second;
          switch (f) {
          case field::byr:
            if (!is_in_range(s, 1920, 2002)) { return false; }
            break;
          case field::iyr:
            if (!is_in_range(s, 2010, 2020)) { return false; }
            break;
          case field::eyr:
            if (!is_in_range(s, 2020, 2030)) { return false; }
            break;
          case field::hgt: {
            if (s.size() < 4) return false;
            auto const unit = s.substr(s.size() - 2, 2);
            auto const num = s.substr(0, s.size() - 2);
            if (unit == "cm") {
              if (!is_in_range(num, 150, 193)) { return false; }
            } else if (unit == "in") {
              if (!is_in_range(num, 59, 76)) { return false; }
            } else {
              return false;
            }
          } break;
          case field::hcl:
            if (s.size() != 7) return false;
            if (s[0] != '#') return false;
            if (s.find_first_not_of("0123456789abcdef", 1) != std::string::npos)
              return false;
            break;
          case field::ecl: {
            static constexpr std::array<std::string_view, 7> colors{
              "amb", "blu", "brn", "gry", "grn", "hzl", "oth"
            };
            auto found = ranges::find(colors, s);
            if (found == colors.end()) return false;
            break;
          }
          case field::pid:
            if (s.size() != 9) return false;
            if (s.find_first_not_of("0123456789") != std::string::npos)
              return false;
            break;
          case field::cid:
          default:
            break;
          }
        }
        return true;
      }
      return false;
    })
    | ranges::to<std::vector>;
  return std::to_string(filtered.size());
}
