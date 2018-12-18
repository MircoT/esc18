#include <dirent.h>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

template <typename T>
std::ostream &operator<<(std::ostream &os, std::vector<T> const &c)
{
  os << "{ ";
  std::copy(std::begin(c), std::end(c), std::ostream_iterator<T>{os, " "});
  os << '}';

  return os;
}

std::vector<std::string> entries(std::unique_ptr<DIR, std::function<int(DIR *)>> dir_ptr)
{
  std::vector<std::string> result;

  // relevant function and data structure are:
  //
  // int  readdir_r(DIR* dirp, struct dirent* entry, struct dirent** result);
  //
  // struct dirent {
  //   // ...
  //   char d_name[256];
  // };
  //
  // dirent entry;
  // for (auto* r = &entry; readdir_r(dir, &entry, &r) == 0 && r; ) {
  //   // `here entry.d_name` is the name of this entry
  // }

  return result;
}

int main(int argc, char *argv[])
{
  std::string const name = argc > 1 ? argv[1] : ".";

  // create a smart pointer to a DIR here, with a deleter
  // relevant functions and data structures are
  // DIR* opendir(const char* name);
  // int  closedir(DIR* dirp);
  auto dir_ptr = std::unique_ptr<DIR, std::function<int(DIR *)>>{
      opendir(const char *name), closedir};

  std::vector<std::string> v = entries(std::move(dir_ptr));
  std::cout << v << '\n';
}
