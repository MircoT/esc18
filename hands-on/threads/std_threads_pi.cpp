#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <numeric>
#include <random>
#include <thread>
#include <vector>

int main()
{
    const unsigned int n_threads = 4;
    constexpr int num_steps = 1 << 20;
    constexpr int step_range = num_steps / n_threads;
    double pi = 0.;
    constexpr double step = 1.0 / (double)num_steps;
    double sum = 0.;

    std::vector<std::thread> my_thread_pool;
    std::mutex my_block;

    auto my_fn = [&](unsigned int my_id) {
        const int start = step_range * my_id;
        double partial_sum = 0;
        for (int i = start; i < start + step_range; ++i)
        {
            auto x = (i + 0.5) * step;
            partial_sum = partial_sum + 4.0 / (1.0 + x * x);
        }
        std::lock_guard<std::mutex> guard(my_block);
        sum += partial_sum;
    };

    for (unsigned int thread_id = 0; thread_id < n_threads; ++thread_id)
    {
        my_thread_pool.emplace_back(std::thread(my_fn, thread_id));
    }

    for (std::thread &cur_thread : my_thread_pool)
    {
        cur_thread.join();
    }

    pi = step * sum;

    std::cout << "Final sum: " << std::setprecision(15) << pi << std::endl;
}