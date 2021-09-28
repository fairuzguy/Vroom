#pragma once

namespace vrm {
    enum class Platform {
        macOS,
        iOS,
        android,
        emscripten,
        windows
    };

    Platform GetCurrentPlatform();
}