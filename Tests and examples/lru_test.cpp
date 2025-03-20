#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>

#include "LRU_cache.hpp" // #include "DecoratorLibrary.hpp"

#define SIZED 0

unsigned long long int func(unsigned int n) {
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    return std::pow(n,n);
}

int main() {
    #if SIZED == 0
    gtd::LRU_cache<unsigned long long int, unsigned int> lru_func(func,2); // gtd::LRU_cache lru_func(func,2);
    #else
    gtd::LRU_cache<unsigned long long int, unsigned int> lru_func(func); // gtd::LRU_cache lru_func(func);
    #endif
    std::cout << lru_func(8u) << std::endl;
    std::cout << lru_func(3u) << std::endl;
    std::cout << lru_func(2u) << std::endl;
    std::cout << lru_func(2u) << std::endl;
    std::cout << lru_func(3u) << std::endl;
    std::cout << lru_func(8u) << std::endl;
    return 0;
}