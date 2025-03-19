#include <iostream>
#include <string>

#include "DecoratorLibrary.hpp"

#define TEMPLATED 0

#if TEMPLATED == 0
template <class rT, class... argTs>
class HelloDecorator: public gtd::Decorator<rT, argTs...> {
public:
    HelloDecorator(rT(*_ptr)(argTs...)) : gtd::Decorator<rT, argTs...>{_ptr} { }
    rT operator()(argTs... args) override {
        std::cout << "That's HelloDecorator's hello!" << std::endl;
        return this->func_ptr(args...);
    }
};
#else
template DecoratorTemplate
struct HelloDecorator: gtdDecoratorChild {
    HelloDecorator DecoratorConstructor
    DecoratorCallOperator {
        std::cout << "That's HelloDecorator's hello!" << std::endl;
        return DecoratorFunctionCall;
    }
};
#endif

float func(const std::string& str, unsigned int n) {
    for(unsigned int i = 0u; i < n; ++i) {
        std::cout << str << std::endl;
    }
    return -3.14 - n;
}

HelloDecorator<float,const std::string&,unsigned int> decorated_func(func); // HelloDecorator decorated_func(func);

int main() {
    std::string str = "C++ is cool!";
    std::cout << decorated_func(str,7u) << std::endl;
    return 0;
}