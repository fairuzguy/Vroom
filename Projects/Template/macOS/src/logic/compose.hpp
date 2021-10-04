#pragma once

#include <algorithm>

namespace vrm {
    template <typename Type1, typename Type2>
    auto ComposeUnion(Type1 func1, Type2 func2) {
        return [func1, func2](auto x) {return std::min(func1(x), func2(x)); };
    }

    template <typename Type1, typename Type2>
    auto ComposeSubtraction(Type1 func1, Type2 func2) {
        return [func1, func2](auto x) {return std::max(-func1(x), func2(x)); };
    }

    template <typename Type1, typename Type2>
    auto ComposeIntersection(Type1 func1, Type2 func2) {
        return [func1, func2](auto x) {return std::max(func1(x), func2(x)); };
    }
}

// Will add smooth boolean compositions at a later stage