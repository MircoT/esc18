#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <numeric>
#include <random>
#include <thread>
#include <vector>
#include <chrono>

int main()
{
    const unsigned int NUM_POINTS = 2<<10;
    float N_in = 0.0f;
    std::random_device rd;        //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(-1.0, 1.0);

    auto const start = std::chrono::high_resolution_clock::now();
    for (unsigned int cur_gen = 0; cur_gen < NUM_POINTS; ++cur_gen)
    {
        float x = dis(gen);
        float y = dis(gen);
        if (x*x + y*y < 1.0f) {
            N_in++;
        }
    }
    auto const end = std::chrono::high_resolution_clock::now();

    std::cout << std::setprecision(15) << "PI: " << (4.0 * N_in) / NUM_POINTS << " calculated in " << (end - start).count() << '\n';
}