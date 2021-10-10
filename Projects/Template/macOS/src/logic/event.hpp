#pragma once

#include <functional>
#include <vector>
#include <map>
#include "function.hpp"

namespace vrm {
    template <typename ReturnType, typename... ParameterTypes>
    class Event {
    public:
        Event() {
            callbacks.clear();
        }
        void Connect(Function<ReturnType, ParameterTypes...> functionPointer) {
            if (callbacks.find(functionPointer) == callbacks.end()) {
                callbacks[functionPointer] = std::vector<Function<ReturnType, ParameterTypes...>>();
            }
            callbacks[functionPointer].push_back(functionPointer);
        }
        void Disconnect(Function<ReturnType, ParameterTypes...> functionPointer) {
            if (callbacks.find(functionPointer) == callbacks.end()) {
                return;
            }
            if (callbacks[functionPointer].size() > 0) {
                callbacks[functionPointer].pop_back();
            }
        }
        void Fire(ParameterTypes... parameters) {
            for (auto const& callbackMapPair : callbacks) {
                for (size_t i = 0; i < callbackMapPair.second.size(); i++) {
                    callbackMapPair.second[i](parameters...);
                }
            }
        }
        ~Event() {
            callbacks.clear();
        }
    private:
        std::map<Function<ReturnType, ParameterTypes...>, std::vector<Function<ReturnType, ParameterTypes...>>> callbacks;
    };
}

// old code; overloading the std::function operators isn't a good idea, need a wrapper for it
/* 
template <typename ReturnType, typename... ParameterTypes>
bool operator<(const std::function<ReturnType(ParameterTypes...)>& func1, const std::function<ReturnType(ParameterTypes...)>& func2) {
    return false;
}

namespace vrm {
    template <typename ReturnType, typename... ParameterTypes>
    class Event {
    public:
        Event() {
            callbacks.clear();
        }
        void Connect(std::function<ReturnType(ParameterTypes...)> functionPointer) {
            if (callbacks.find(functionPointer) == callbacks.end()) {
                callbacks[functionPointer] = std::vector<std::function<ReturnType(ParameterTypes...)>>();
            }
            callbacks[functionPointer].push_back(functionPointer);
        }
        void Disconnect(std::function<ReturnType(ParameterTypes...)> functionPointer) {
            if (callbacks.find(functionPointer) == callbacks.end()) {
                return;
            }
            if (callbacks[functionPointer].size() > 0) {
                callbacks[functionPointer].pop_back();
            }
        }
        void Fire(ParameterTypes... parameters) {
            for (auto const& callbackMapPair : callbacks) {
                for (size_t i = 0; i < callbackMapPair.second.size(); i++) {
                    callbackMapPair.second[i](parameters...);
                }
            }
        }
        ~Event() {
            callbacks.clear();
        }
    private:
        std::map<std::function<ReturnType(ParameterTypes...)>, std::vector<std::function<ReturnType(ParameterTypes...)>>> callbacks;
    };
} */