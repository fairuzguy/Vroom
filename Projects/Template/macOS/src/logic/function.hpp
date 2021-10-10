#pragma once

#include <functional>

namespace vrm {
    template<typename ReturnType, typename... ParameterTypes>
    class Function {
    public:
        Function(std::function<ReturnType(ParameterTypes...)> newFunctionPointer) {
            functionPointer = newFunctionPointer;
        }
        bool operator<(const Function<ReturnType, ParameterTypes...>& func) const {
            return false;
        }
        ReturnType operator()(const ParameterTypes&... parameters) const {
            return functionPointer(parameters...);
        }
    private:
        std::function<ReturnType(ParameterTypes...)> functionPointer;
    };
}