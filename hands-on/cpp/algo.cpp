#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

std::ostream &operator<<(std::ostream &os, std::vector<int> const &c);
std::vector<int> make_vector(int N);

int main() {
  // create a vector of N elements, generated randomly
  int const N = 10;
  std::vector<int> v = make_vector(N);
  std::cout << "==> Vector: " << v << '\n';

  // sum all the elements of the vector
  // use std::accumulate
  auto elm_sum = std::accumulate(v.begin(), v.end(), 0);
  std::cout << "==> Sum of all elemnts with accumulator: " << elm_sum << '\n';

  // compute the average of the first half and of the second half of the vector
  auto const half_size = v.size() / 2;
  auto first_half_avg = std::accumulate(v.begin(), v.begin() + half_size, 0.0);
  auto second_half_avg = std::accumulate(v.begin() + half_size, v.end(), 0.0);
  std::cout << "==> first half avg: " << first_half_avg / half_size << '\n';
  std::cout << "==> second half avg: " << second_half_avg / half_size << '\n';

  // move the three central elements to the beginning of the vector
  // use std::rotate
  assert(v.size() > 3);
  std::rotate(v.begin(), v.begin() + half_size - 1, v.begin() + half_size + 1);
  std::cout << "==> Rotaded Vector: " << v << '\n';

  // remove duplicate elements
  // use std::sort followed by std::unique/unique_copy
  std::sort(v.begin(), v.end());
  std::cout << "==> Sorted Vector: " << v << '\n';

  std::vector<int> unique_v;
  std::unique_copy(v.begin(), v.end(), std::back_inserter(unique_v));
  std::cout << "==> Unique Vector: " << unique_v << '\n';
};

std::ostream &operator<<(std::ostream &os, std::vector<int> const &c) {
  os << "{ ";
  std::copy(std::begin(c), std::end(c), std::ostream_iterator<int>{os, " "});
  os << '}';

  return os;
}

std::vector<int> make_vector(int N) {
  std::random_device rd;
  std::mt19937 eng{rd()};

  int const MAX_N = 100;
  std::uniform_int_distribution<int> dist{1, MAX_N};

  std::vector<int> result;
  result.reserve(N);
  std::generate_n(std::back_inserter(result), N, [&]() { return dist(eng); });

  return result;
}
