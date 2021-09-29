#pragma once

#include "../platform/graphics-wrapper.hpp"
#include "../platform/glm-wrapper.hpp"
#include <string>

namespace vrm {
    class OpenGLPipeline {
    public:
        OpenGLPipeline(const std::string& shaderName);
        void Render(const glm::mat4& mvp) const;
        ~OpenGLPipeline();
    private:
        const GLuint shaderProgramId;
        const GLuint uniformLocationMVP;
        const GLuint uniformLocationCounter;
        const GLuint uniformLocationiResolution;
        const GLuint attributeLocationVertexPosition;
    };
}