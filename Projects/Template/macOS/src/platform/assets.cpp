#include "assets.hpp"
#include "sdl-wrapper.hpp"
#include <string>

namespace vrm {
    std::string LoadTextFile(const std::string& path) {
        SDL_RWops* file = SDL_RWFromFile(path.c_str(), "r");
        size_t fileLength = static_cast<size_t>(SDL_RWsize(file));
        void* data = SDL_LoadFile_RW(file, nullptr, 1);
        std::string result = std::string(static_cast<char*>(data), fileLength);
        SDL_free(data);

        return result;
    }
}