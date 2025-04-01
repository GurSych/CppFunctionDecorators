#pragma once

#include <unordered_map>
#include <utility>
#include <tuple>
#include <list>

#include <functional>
namespace std {
    template <typename... Ts>
    class hash<std::tuple<Ts...>> {
    public:
        std::size_t operator()(const std::tuple<Ts...>& _tuple) const {
            return std::apply([](const Ts&... args) { 
                return (00 ^ ... ^ std::hash<std::decay_t<Ts>>{}(args));
            }, _tuple);
        }
    };
}

namespace gtd {
    template <typename rT, typename... argTs>
    class LRU_cache {
    public:
        explicit LRU_cache(rT(*_ptr)(argTs...)) : __func_ptr{_ptr} {}
        explicit LRU_cache(rT(*_ptr)(argTs...), std::size_t _size) : __func_ptr{_ptr}, __cache_size{_size} {}
        rT operator()(argTs... args) {
            std::tuple<argTs...> tuple_args = std::make_tuple(args...);
            if(__cache_map.count(tuple_args)) {
                __cache.splice(__cache.begin(),__cache,__cache_map[tuple_args]);
                return __cache_map[tuple_args]->second;
            } else {
                if(__cache_size != 0ull) { if(__cache_map.size() == __cache_size) {
                    __cache_map.erase(__cache.back().first);
                    __cache.pop_back();
                } }
                rT _return = __func_ptr(args...);
                __cache.push_front({tuple_args,_return});
                __cache_map[tuple_args] = __cache.begin();
                return _return;
            }
        }
        std::size_t cache_size() {
            return __cache_map.size();
        }
        void change_cache_size(std::size_t new_size) {
            if(new_size >= cache_size()) return;
            while(cache_size() > new_size) {
                __cache_map.erase(__cache.back().first);
                __cache.pop_back();
            }
        }
        std::size_t cache_capacity() {
            return __cache_size;
        }
        void change_cache_capacity(std::size_t new_size) {
            if((__cache_size > new_size || __cache_size == 0) && new_size != 0) {
                while(cache_size() > new_size) {
                    __cache_map.erase(__cache.back().first);
                    __cache.pop_back();
                }
            }
            __cache_size = new_size;
        }
        void clear_cache() {
            __cache_map.clear();
            __cache.clear();
        }
        void clear_cache(argTs... args) {
            clear_cache(std::make_tuple(args...));
        }
        void clear_cache(std::tuple<argTs...> args) {
            __cache.erase(__cache_map[args]);
            __cache_map.erase(args);
        }
    private:
        rT(*__func_ptr)(argTs...){};
        std::size_t __cache_size{};
        std::list<std::pair<std::tuple<argTs...>,rT>> __cache{};
        std::unordered_map<std::tuple<argTs...>, typename std::list<std::pair<std::tuple<argTs...>,rT>>::iterator> __cache_map{};
    };
}