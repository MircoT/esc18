## compile example
# g++ -std=c++17 -L$(pwd)/tbb/lib -I$(pwd)/tbb/include -ltbb -Wall -O3 -o hello_world_tbb hello_world_tbb.cpp

DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:`pwd`/tbb/lib $@
