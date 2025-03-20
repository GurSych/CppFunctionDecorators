#include <iostream>
#include <thread>
#include <chrono>
#include <functional>

#include "LRU_cache.hpp" // #include "DecoratorLibrary.hpp"

class Base {
public:
    Base(unsigned int _n) : n{_n} {}
    unsigned int n {};
    bool operator==(const Base& _obj) const {
        return this->n == _obj.n;
    }
};
    
template <>
class std::hash<Base> {
public:
    std::size_t operator()(const Base& _obj) const {
        return std::hash<unsigned int>{}(_obj.n);
    }
};

unsigned int func(Base obj) {
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    return obj.n;
}

int main() {
    Base obj(7u);
    gtd::LRU_cache<unsigned int, Base> lru_func(func); // gtd::LRU_cache lru_func(func);
    std::cout << lru_func(obj) << std::endl;
    std::cout << lru_func(obj) << std::endl;
    return 0;
}