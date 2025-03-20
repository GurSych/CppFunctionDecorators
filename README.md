# CppFunctionDecorators

Decorator Library is my C++ library for creating various function decorators. It also provides several ready-to-use decorators

# Using Library

> Library is in development so this section is updated together with library itself

## Library connection

```cpp
#include "DecoratorLibrary.hpp"
```

> [!NOTE]
> All library classes are in `gtd::` namespace

> This section is in development...

## LRU_cache

Library provides you with a `gtd::LRU_cache` class. Its consturctor takes a _function pointer_ and creates a callable function object. This object saves returned value for each first call with unique set of arguments. The constuctor can also takes a second argument with `std::size_t` type - number of cache cells.

```cpp
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>

#include "LRU_cache.hpp" // #include "DecoratorLibrary.hpp"

unsigned long long int func(unsigned int n) {
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    return std::pow(n,n);
}

int main() {
    gtd::LRU_cache<unsigned long long int, unsigned int> lru_func(func,2); // gtd::LRU_cache lru_func(func,2);
    std::cout << lru_func(8u) << std::endl;
    std::cout << lru_func(3u) << std::endl;
    std::cout << lru_func(2u) << std::endl;
    std::cout << lru_func(2u) << std::endl;
    std::cout << lru_func(3u) << std::endl;
    std::cout << lru_func(8u) << std::endl;
    return 0;
}
```

This code has a simple long-computing function (it just sleeps for two seconds before returning std::pow). This function are sent to `lru_func`'s constructor with `std::size_t` value of two. First three calls are computed for two seconds because they have unique sets of arguments. Cache has only two cells so this object saves only last two calls. That's because the 4th and 5th calls return their values instantly but 6th one are computed for two seconds again.

> [!WARNING]
> The type of each argument must be hashable via std::hash. Override std::hash if your function takes an object of a class as an argument.

# Versions

**Current version: 1.1.0**

+ 1.x.x
  + 1.1.x
    + 1.1.0 - LRU_cache added
  + 1.0.x
    + 1.0.0 - base functional of Decorator base-class
