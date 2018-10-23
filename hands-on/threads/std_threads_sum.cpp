#include <functional>
#include <iostream>
#include <mutex>
#include <numeric>
#include <random>
#include <thread>
#include <vector>
#include <cmath>

std::vector<int> make_vector(int N, int const MAX_N)
{
    std::random_device rd;
    std::mt19937 eng{rd()};
    std::uniform_int_distribution<int> dist{1, MAX_N};

    std::vector<int> result;
    result.reserve(N);
    std::generate_n(std::back_inserter(result), N, [&]() { return dist(eng); });

    return result;
}

int main()
{
    int const SIZE = std::pow(2, 16);
    std::vector<int> my_vector = make_vector(SIZE, 1);
    const unsigned int n_threads = 256;
    const int partition_size = my_vector.size() / n_threads;
    unsigned int global_counter = 0;
    std::vector<std::thread> my_thread_pool;
    std::mutex my_block;

    auto my_fn = [&](unsigned int my_id) {
        auto start = my_vector.begin() + partition_size * my_id;
        int sum = std::accumulate(start, start + partition_size, 0);
        std::lock_guard<std::mutex> guard(my_block);
        global_counter += sum;
    };

    for (unsigned int thread_id = 0; thread_id < n_threads; ++thread_id)
    {
        my_thread_pool.emplace_back(
            std::thread(
                my_fn,
                thread_id));
    }

    for (std::thread &cur_thread : my_thread_pool)
    {
        cur_thread.join();
    }

    std::cout << "Final sum: " << global_counter;
}