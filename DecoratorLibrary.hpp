#pragma once

#include "LRU_cache.hpp"

#define DecoratorTemplate <class rT, class... argTs>
#define DecoratorTemplateTypes <rT, argTs...>
#define DecoratorCallOperator rT operator()(argTs... args) override
#define DecoratorFunctionCall this->func_ptr(args...)
#define gtdDecoratorChild public gtd::Decorator<rT, argTs...>
#define DecoratorConstructor (rT(*_ptr)(argTs...)) : gtd::Decorator<rT, argTs...>{_ptr} { }

namespace gtd {
    template <class rT, class... argTs>
    class Decorator {
    public:
        explicit Decorator(rT(*_ptr)(argTs...)) : func_ptr{_ptr} {}
        virtual rT operator()(argTs... args) {
            rT _return = this->func_ptr(args...);
            std::cout << "This function was decorated via Decorator by Gur-Sych" << std::endl;
            return _return;
        }
    protected:
        rT(*func_ptr)(argTs...){};
    };
}