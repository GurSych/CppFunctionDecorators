#pragma once

#include <unordered_map>
#include <iterator>
#include <utility>
#include <tuple>
#include <list>

#include <functional>
namespace std {
    template <class... Ts>
    class hash<std::tuple<Ts...>> {
    public:
        std::size_t operator()(const std::tuple<Ts...>& _tuple) const {
            return std::apply([](const Ts&... args) { 
                return (... ^ std::hash<std::decay_t<Ts>>{}(args));
            }, _tuple);
        }
    };
}

namespace gtd {
    template <class rT, class... argTs>
    class LRU_cache {
    public:
        explicit LRU_cache(rT(*_ptr)(argTs...)) : func_ptr{_ptr} {}
        explicit LRU_cache(rT(*_ptr)(argTs...), std::size_t _size) : func_ptr{_ptr}, cache_size{_size} {}
        rT operator()(argTs... args) {
            std::tuple<argTs...> tuple_args = std::make_tuple(args...);
            if(cache_map.count(tuple_args)) {
                cache.splice(cache.begin(),cache,cache_map[tuple_args]);
                return cache_map[tuple_args]->second;
            } else {
                if(cache_size != 0ull) { if(cache_map.size() == cache_size) {
                    cache_map.erase(cache.back().first);
                    cache.pop_back();
                } }
                rT _return = func_ptr(args...);
                cache.push_front({tuple_args,_return});
                cache_map[tuple_args] = cache.begin();
                return _return;
            }
        }
    private:
        rT(*func_ptr)(argTs...){};
        std::size_t cache_size{};
        std::list<std::pair<std::tuple<argTs...>,rT>> cache{};
        std::unordered_map<std::tuple<argTs...>, typename std::list<std::pair<std::tuple<argTs...>,rT>>::iterator, std::hash<std::tuple<argTs...>>> cache_map{};
    };
}