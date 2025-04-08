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
        /// @param _ptr the function pointer.
        explicit LRU_cache(rT(*_ptr)(argTs...)) : __func_ptr{_ptr} {}
        /// @param _ptr the function pointer.
        /// @param _size the maximum size of the cache.
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
        /// @brief Returns the size of the cache.
        /// @return Cache size as std::size_t.
        std::size_t cache_size() const {
            return __cache_map.size();
        }
        /// @brief Reduces the size of the cache to the specified size.
        /// @param new_size the new size of the cache as std::size_t.
        void reduce_cache_size(std::size_t new_size) {
            while(cache_size() > new_size) {
                __cache_map.erase(__cache.back().first);
                __cache.pop_back();
            }
        }
        /// @brief Returns the maximum size of the cache.
        /// @return Maximum cache size as std::size_t (0 - if an infinity size).
        std::size_t cache_capacity() const {
            return __cache_size;
        }
        /// @brief Changes the maximum size of the cache to the specified size.
        /// @param new_size the new maximum size of the cache as std::size_t (0 - to an infinity size).
        void change_cache_capacity(std::size_t new_size) {
            if((__cache_size > new_size || __cache_size == 0) && new_size != 0) {
                while(cache_size() > new_size) {
                    __cache_map.erase(__cache.back().first);
                    __cache.pop_back();
                }
            }
            __cache_size = new_size;
        }
        /// @brief Clear the all cache.
        void clear_cache() {
            __cache_map.clear();
            __cache.clear();
        }
        /// @brief Clear the cache's entry with the specified arguments.
        /// @param args... the set of the function's arguments.
        void clear_cache(argTs... args) {
            clear_cache(std::make_tuple(args...));
        }
        /// @brief Clear the cache's entry with the specified arguments.
        /// @param args the set of the function's arguments as std::tuple.
        void clear_cache(std::tuple<argTs...> args) {
            if(__cache_map.count(args) == 0) return;
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