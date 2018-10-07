#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <iterator>
#include <dirent.h>

template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> const& c)
{
  os << "{ ";
  std::copy(
      std::begin(c),
      std::end(c),
      std::ostream_iterator<T>{os, " "}
  );
  os << '}';

  return os;
}

std::vector<std::string> entries(/* add the right arguments here */)
{
  std::vector<std::string> result;

  // // dir has type DIR*
  // dirent entry;
  // for (auto* r = &entry; readdir_r(dir, &entry, &r) == 0 && r; ) {
  //   // `here entry.d_name` is the name of this entry
  // }

  return result;
}

int main(int argc, char* argv[])
{
  std::string const name = argc > 1 ? argv[1] : ".";

  // create a smart pointer to a DIR here, with a deleter
  // relevant functions and data structures are
  // DIR *opendir(const char *name);
  // int closedir(DIR *dirp);
  // int readdir_r(DIR *dirp, struct dirent *entry, struct dirent **result);
  // 
  // struct dirent {
  //   // ...
  //   char d_name[256];
  // };

  auto v = entries(/* add the right argument here */);
  std::cout << v << '\n';
}

