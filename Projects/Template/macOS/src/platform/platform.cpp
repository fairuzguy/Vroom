#include "platform.hpp"

namespace vrm {
    Platform GetCurrentPlatform() {
#ifdef __EMSCRIPTEN__
        return Platform::emscripten;
#elif __APPLE__
#include "TargetConditionals.h"
#if TARGET_OS_IPHONE
        return Platform::iOS;
#else
        return Platform::macOS;
#endif
#elif __ANDROID__
        return Platform::android;
#elif WIN32
        return Platform::windows;
#endif
    }
}