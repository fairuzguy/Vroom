#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "sdl-wrapper.hpp"
#include "platform.hpp"

namespace vrm {
    bool ShouldDisplayFullscreen() {
        switch (GetCurrentPlatform()) {
            case Platform::iOS:
            case Platform::android:
                return true;
            default:
                return false;
        }
    }

    std::pair<uint32_t, uint32_t> GetDisplaySize() {
        uint32_t displayWidth = 0;
        uint32_t displayHeight = 0;

#ifdef __EMSCRIPTEN__
        displayWidth = static_cast<uint32_t>(EM_ASM_INT({
            return document.getElementById('canvas').width;
        }));
        displayHeight = static_cast<uint32_t>(EM_ASM_INT({
            return document.getElementById('canvas').height;
        }));
#else
        switch (GetCurrentPlatform()) {
            case Platform::iOS:
            case Platform::android: {
                SDL_DisplayMode displayMode;
                SDL_GetDesktopDisplayMode(0, &displayMode);
                displayWidth = static_cast<uint32_t>(displayMode.w);
                displayHeight = static_cast<uint32_t>(displayMode.h);
                break;
            }
            default: {
                displayWidth = 640;
                displayHeight = 640;
                break;
            }
        }
#endif
        return std::make_pair(displayWidth, displayHeight);
    }

    SDL_Window* CreateWindow(const uint32_t& windowFlags) {
        std::pair<uint32_t, uint32_t> displaySize = GetDisplaySize();
        SDL_Window* window = SDL_CreateWindow(
            "Template",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            displaySize.first, displaySize.second,
            windowFlags);
        if (ShouldDisplayFullscreen()) {
            SDL_SetWindowFullscreen(window, SDL_TRUE);
        }
        return window;
    }
}