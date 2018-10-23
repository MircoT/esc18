#include <memory>

// int* factory();

// // "still reachable"
// auto g = factory();

// int main()
// {
//   // "definitely lost"
//   auto t = factory();
// }

// int* factory()
// {
//   return new int;
// }

std::unique_ptr<int> factory();

// "still reachable"
auto g = factory();

int main()
{
  // "definitely lost"
  auto t = factory();
}

std::unique_ptr<int> factory()
{
  return std::make_unique<int>();
}
