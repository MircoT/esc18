#include <cassert>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <utility>

using Duration = std::chrono::duration<float>;

std::pair<double, Duration> pi(int n)
{
  assert(n > 0);

  auto const start = std::chrono::high_resolution_clock::now();

  auto const step = 1. / n;
  auto sum = 0.;
  for (int i = 0; i != n; ++i)
  {
    auto x = (i + 0.5) * step;
    sum += 4. / (1. + x * x);
  }

  auto const end = std::chrono::high_resolution_clock::now();

  return {step * sum, end - start};
}

constexpr float static_pi(int n)
{
  auto const step = 1. / n;
  auto sum = 0.;
  for (int i = 0; i != n; ++i)
  {
    auto x = (i + 0.5) * step;
    sum += 4. / (1. + x * x);
  }
  return step * sum;
}

int main(int argc, char *argv[])
{
  int const n = (argc > 1) ? std::atoi(argv[1]) : 10;
  auto const [value, time] = pi(n);

  auto const start = std::chrono::high_resolution_clock::now();
  auto const value2 = static_pi(n);
  auto const end = std::chrono::high_resolution_clock::now();

  std::cout << "pi = " << value << " for " << n << " iterations"
            << " in " << time.count() << " s\n";

  std::cout << "pi = " << value2 << " for " << n << " iterations"
            << " in " << (start - end).count() << " s\n";
}
