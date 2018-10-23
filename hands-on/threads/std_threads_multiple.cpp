#include <iostream>
#include <thread>
#include <vector>

int main()
{
    auto my_fn = [](unsigned int my_id, unsigned int count) {
        for (unsigned int cur_count = 1; cur_count <= count; ++cur_count)
            std::cout << "[Thread][" << my_id << "][" << std::thread::id()
                      << "] I counted " << cur_count << std::endl
                      << std::flush;
    };
    const unsigned int n_threads = 42;
    const unsigned int max_count = 42;

    std::vector<std::thread> thread_pool;

    for (unsigned int thread_id = 0; thread_id < n_threads; ++thread_id)
    {
        thread_pool.emplace_back(std::thread(my_fn, thread_id, max_count));
    }

    for (std::thread &cur_thread : thread_pool)
    {
        cur_thread.join();
    }
}