#pragma once

#include <SDL.h>
#include <utility>

namespace vrm {
    bool ShouldDisplayFullscreen();
    std::pair<uint32_t, uint32_t> GetDisplaySize();
    SDL_Window* CreateWindow(const uint32_t& windowFlags);
}