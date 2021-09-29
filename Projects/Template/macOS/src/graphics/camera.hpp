#pragma once

#include "../platform/glm-wrapper.hpp"

namespace vrm {
    class Camera {
    public:
        Camera(const float& width, const float& height);
        const glm::mat4& GetProjectionMatrix() const;
        const glm::mat4& GetViewMatrix() const;
    private:
        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;
    };
}