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

> This section is in development...

<details>
<summary>Code example</summary>

> This section is in development...

```cpp
#include <iostream>
#include "LRU_cache.hpp" // #include "DecoratorLibrary.hpp"
#include <cmath>
#include <thread>
#include <chrono>

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

</details>

# Versions

**Current version: 1.1.0**

+ 1.x.x
  + 1.1.x
    + 1.1.0 - LRU_cache added
  + 1.0.x
    + 1.0.0 - base functional of Decorator base-class
