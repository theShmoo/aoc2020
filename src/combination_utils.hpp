#pragma once

#include <algorithm>
#include <cmath>

namespace utils {

inline unsigned int factorial(unsigned int const factor)
{
  return static_cast<unsigned int>(std::tgamma(factor + 1.0));
}

inline unsigned int num_combinations(unsigned int const num_items,
  unsigned int const chosen_items_at_time)
{
  return factorial(num_items)
         / (factorial(chosen_items_at_time)
            * factorial(num_items - chosen_items_at_time));
}

template<typename Iterator>
bool next_combination(const Iterator first, Iterator k, const Iterator last)
{
  /* Credits: Mark Nelson http://marknelson.us */
  if ((first == last) || (first == k) || (last == k)) return false;
  Iterator i1 = first;
  Iterator i2 = last;
  ++i1;
  if (last == i1) return false;
  i1 = last;
  --i1;
  i1 = k;
  --i2;
  while (first != i1) {
    if (*--i1 < *i2) {
      Iterator j = k;
      while (!(*i1 < *j)) ++j;
      std::iter_swap(i1, j);
      ++i1;
      ++j;
      i2 = k;
      std::rotate(i1, j, last);
      while (last != j) {
        ++j;
        ++i2;
      }
      std::rotate(k, i2, last);
      return true;
    }
  }
  std::rotate(first, k, last);
  return false;
}
}// namespace utils