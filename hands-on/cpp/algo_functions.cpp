#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

std::ostream &operator<<(std::ostream &os, std::vector<int> const &c);
std::vector<int> make_vector(int N);

int main()
{
  // create a vector of N elements, generated randomly
  int const N = 10;
  std::vector<int> v = make_vector(N);
  std::cout << "==> Vector: " << v << '\n';

  // multiply all the elements of the vector
  // use std::accumulate
  auto product =
      std::accumulate(std::begin(v), std::end(v), 1LL, std::multiplies<>());
  std::cout << "==> Product with multiplies: " << product << '\n';

  product = std::accumulate(
      std::begin(v), std::end(v), 1LL,
      [](long long first, long long second) { return first * second; });
  std::cout << "==> Product with lambda: " << product << '\n';

  // sort the vector in descending order
  // use std::sort
  std::sort(std::begin(v), std::end(v), std::greater<>());
  std::cout << "==> Vector sorted descending: " << v << '\n';

  // move the even numbers at the beginning of the vector
  // use std::partition
  std::partition(std::begin(v), std::end(v), [](int elm) { return elm % 2; });
  std::cout << "==> Vector partitioned: " << v << '\n';

  // create another vector with the squares of the numbers in the first vector
  // use std::transform
  std::vector<int> square_v;
  std::transform(std::begin(v), std::end(v), std::back_inserter(square_v),
                 [](int elm) { return elm * elm; });
  std::cout << "==> Vector partitioned square: " << square_v << '\n';

  // find the first multiple of 3 or 7
  // use std::find_if
  auto first_by_3_or_7 =
      std::find_if(std::begin(v), std::end(v),
                   [](int value) { return value % 3 == 0 || value % 7 == 0; });

  if (first_by_3_or_7 != std::end(v))
  {
    std::cout << "First element multiple of 3 or 7 is: " << *first_by_3_or_7
              << '\n';
  }
  else
  {
    std::cout << "There is not multiples of 3 or 7...\n";
  }

  // erase from the vector all the multiples of 3 or 7
  // use std::remove_if followed by vector::erase
  v.erase(
      std::remove_if(
          std::begin(v),
          std::end(v),
          [](int value) { return value % 3 == 0 || value % 7 == 0; }),
      std::end(v));
  std::cout << "==> Vector without multiples of 3 or 7: " << v << '\n';
};

std::ostream &operator<<(std::ostream &os, std::vector<int> const &c)
{
  os << "{ ";
  std::copy(std::begin(c), std::end(c), std::ostream_iterator<int>{os, " "});
  os << '}';

  return os;
}

std::vector<int> make_vector(int N)
{
  // define a pseudo-random number generator engine and seed it using an actual
  // random device
  std::random_device rd;
  std::mt19937 eng{rd()};
  // std::mt19937 eng{5};

  int const MAX_N = 100;
  std::uniform_int_distribution<int> dist{1, MAX_N};

  std::vector<int> result;
  result.reserve(N);
  std::generate_n(std::back_inserter(result), N, [&]() { return dist(eng); });

  return result;
}
