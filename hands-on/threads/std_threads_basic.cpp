#include <thread>
#include <iostream>

int main()
{
    auto my_fn = [](unsigned int i){
        std::cout << "[Thread][" << i << "] Hello world from thread "<< std::endl;
    };

    std::thread t_0(my_fn, 0);
    t_0.join();
}