#include <iostream>
#include <thread>
#include <vector>

int main()
{
    auto my_fn = [](unsigned int my_id, unsigned int &count) {
        std::cout << "[Thread][" << my_id << "][" << std::thread::id()
                  << "] I counted " << count++ << " and I add +1" << std::endl
                  << std::flush;
    };
    const unsigned int n_threads = 42;
    unsigned int counter = 0;

    std::vector<std::thread> thread_pool;

    for (unsigned int thread_id = 0; thread_id < n_threads; ++thread_id)
    {
        thread_pool.emplace_back(std::thread(my_fn, thread_id, std::ref(counter)));
    }

    for (std::thread &cur_thread : thread_pool)
    {
        cur_thread.join();
    }

    std::cout << "Final sum: " << counter;
}