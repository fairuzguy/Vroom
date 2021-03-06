#pragma once

#include "../platform/graphics-wrapper.hpp"
#include "../platform/glm-wrapper.hpp"
#include "../platform/sdl-wrapper.hpp"
#include <string>

namespace vrm {
    class OpenGLPipeline {
    public:
        OpenGLPipeline(const std::string& shaderName);
        void Render(SDL_Window* window, const glm::mat4& mvp, float counter) const;
        ~OpenGLPipeline();
    private:
        const GLuint shaderProgramId;
        const GLuint uniformLocationMVP;
        const GLuint uniformLocationCounter;
        const GLuint uniformLocationiResolution;
        const GLuint uniformLocationSDFCoreData;
        const GLuint uniformLocationSDFRenderData;
        const GLuint uniformLocationExpressionList;
        const GLuint uniformLocationSDFList;
        const GLuint attributeLocationVertexPosition;
    };
}