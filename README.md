# CppFunctionDecorators

Decorator Library is my C++ library for creating various function decorators. It also provides several ready-to-use decorators

# Using Library

> The library is in development so this section is updated together with library itself

## Library connection

```cpp
#include "DecoratorLibrary.hpp"
```

> [!NOTE]
> All library classes are in `gtd::` namespace.

Decorator is a class which constuctor takes a _function pointer_ and saves it. The resulting object is callable and takes the same arguments' types.<br>
The library provides you with a `gtd::Decorator` base-class. To create your own decorator you should create an inherited class and override its _call operator_.

```cpp
#include <iostream>
#include <string>

#include "DecoratorLibrary.hpp"

template <class rT, class... argTs>
class HelloDecorator: public gtd::Decorator<rT, argTs...> {
public:
    HelloDecorator(rT(*_ptr)(argTs...)) : gtd::Decorator<rT, argTs...>{_ptr} { }
    rT operator()(argTs... args) override {
        std::cout << "That's HelloDecorator's hello!" << std::endl;
        return this->func_ptr(args...);
    }
};

float func(const std::string& str, unsigned int n) {
    for(unsigned int i = 0u; i < n; ++i) {
        std::cout << str << std::endl;
    }
    return -3.14f - n;
}

HelloDecorator<float,const std::string&,unsigned int> decorated_func(func); // HelloDecorator decorated_func(func);

int main() {
    std::string str = "C++ is cool!";
    std::cout << decorated_func(str,7u) << std::endl;
    return 0;
}
```

<details>
<summary>About macros</summary>

The library contains several macros that can simplify its usage.

```cpp
template DecoratorTemplate
struct HelloDecorator: gtdDecoratorChild {
    HelloDecorator DecoratorConstructor
    DecoratorCallOperator {
        std::cout << "That's HelloDecorator's hello!" << std::endl;
        return DecoratorFunctionCall;
    }
};
```

</details>

This code shows you HelloDecorator class that can take any function and writes hello before calling this function itself when it is called.

> [!TIP]
> You can use empty `template <>` and choose the class' types you need or even use more difficult templates.

## LRU_cache

The library provides you with a `gtd::LRU_cache` class. Its consturctor takes a _function pointer_ and creates a callable function object. This object saves returned value for each first call with unique set of arguments. The constuctor can also takes a second argument with `std::size_t` type - size of cache (number of cells).

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
    std::cout << lru_func(8u) << std::endl; // 2 seconds
    std::cout << lru_func(3u) << std::endl; // 2 seconds
    std::cout << lru_func(2u) << std::endl; // 2 seconds
    std::cout << lru_func(2u) << std::endl; // Instantly
    std::cout << lru_func(3u) << std::endl; // Instantly
    std::cout << lru_func(8u) << std::endl; // 2 seconds
    return 0;
}
```

<img src="Tests and examples\lru_test.gif" alt="LRU_cache demonstration" width="100%">

This code has a simple long-computing function (it just sleeps for two seconds before returning std::pow). This function are sent to `lru_func`'s constructor with `std::size_t` value of two. First three calls are computed for two seconds because they have unique sets of arguments. Cache has only two cells so this object saves only last two calls. That's because the 4th and 5th calls return their values instantly but 6th one are computed for two seconds again.

> [!WARNING]
> The type of each argument must be hashable via `std::hash`. Override `std::hash` if your function takes an object of a class as an argument.

# Versions

**Current version: 1.1.0**

+ 1.x.x
  + 1.1.x
    + 1.1.0 - LRU_cache added
  + 1.0.x
    + 1.0.0 - base functional of Decorator base-class
