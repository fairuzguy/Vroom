#include "camera.hpp"

namespace vrm {
    glm::mat4 CreateProjectionMatrix(const float& width, const float& height) {
        return glm::perspective(glm::radians(60.0f), width/height, 0.01f, 100.0f);
    }

    glm::mat4 CreateViewMatrix() {
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 2.0f);
        glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        return glm::lookAt(position, target, up);
    }

    Camera::Camera(const float& width, const float& height) :
        projectionMatrix(CreateProjectionMatrix(width, height)),
        viewMatrix(CreateViewMatrix()) {
    }

    const glm::mat4& Camera::GetProjectionMatrix() const {
        return projectionMatrix;
    }
    
    const glm::mat4& Camera::GetViewMatrix() const {
        return viewMatrix;
    }
}