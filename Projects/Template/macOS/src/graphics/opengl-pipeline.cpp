#include "opengl-pipeline.hpp"
#include "../platform/assets.hpp"
#include "../platform/sdl-wrapper.hpp"
#include "../debug/debug.hpp"
#include <stdexcept>
#include <vector>

namespace vrm {
    GLuint CompileShader(const GLenum& shaderType, const std::string& shaderSource) {
        GLuint shaderId = glCreateShader(shaderType);
        const char* shaderData = shaderSource.c_str();
        glShaderSource(shaderId, 1, &shaderData, nullptr);
        glCompileShader(shaderId);
        GLint shaderCompilationResult;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &shaderCompilationResult);

        if (!shaderCompilationResult) {
            GLint errorMessageLength;
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &errorMessageLength);
            std::vector<char> errorMessage(errorMessageLength + 1);
            glGetShaderInfoLog(shaderId, errorMessageLength, nullptr, &errorMessage[0]);
            print(&errorMessage[0]);
            throw std::runtime_error("OpenGL shader failed to compile! Aborting.");
        }
        
        return shaderId;
    }

    GLuint CreateShaderProgram(const std::string& shaderName) {
        print("Creating pipeline for '" + shaderName + "'");
        const std::string vertexShaderCode = LoadTextFile("assets/shaders/opengl/" + shaderName + ".vert");
        const std::string fragmentShaderCode = LoadTextFile("assets/shaders/opengl/" + shaderName + ".frag");
#ifdef USING_GLES
        std::string vertexShaderSource = "#version 100\n" + vertexShaderCode;
        std::string fragmentShaderSource = "#version 100\nprecision mediump float;\n" + fragmentShaderCode;
#else
        std::string vertexShaderSource = "#version 120\n" + vertexShaderCode;
        std::string fragmentShaderSource = "#version 120\n" + fragmentShaderCode;
#endif
        GLuint shaderProgramId = glCreateProgram();
        GLuint vertexShaderId = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
        GLuint fragmentShaderId = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
        glAttachShader(shaderProgramId, vertexShaderId);
        glAttachShader(shaderProgramId, fragmentShaderId);
        glLinkProgram(shaderProgramId);
        GLint shaderProgramLinkResult;
        glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &shaderProgramLinkResult);

        if (!shaderProgramLinkResult) {
            GLint errorMessageLength;
            glGetProgramiv(shaderProgramId, GL_INFO_LOG_LENGTH, &errorMessageLength);
            std::vector<char> errorMessage(errorMessageLength + 1);
            glGetProgramInfoLog(shaderProgramId, errorMessageLength, nullptr, &errorMessage[0]);
            print(&errorMessage[0]);
            throw std::runtime_error("OpenGL shader program failed to compile! Aborting.");
        }

        glDetachShader(shaderProgramId, vertexShaderId);
        glDetachShader(shaderProgramId, fragmentShaderId);
        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);

        return shaderProgramId;
    }

    GLuint CreateVertexBuffer(const std::vector<glm::vec3> vertices) {
        std::vector<float> bufferData;
        for (const glm::vec3 vertex : vertices) {
            bufferData.push_back(vertex.x);
            bufferData.push_back(vertex.y);
            bufferData.push_back(vertex.z);
        }
        GLuint bufferId;
        glGenBuffers(1, &bufferId);
        glBindBuffer(GL_ARRAY_BUFFER, bufferId);
        glBufferData(
            GL_ARRAY_BUFFER,
            bufferData.size()*sizeof(float),
            bufferData.data(),
            GL_STATIC_DRAW
        );
        return bufferId;
    }

    GLuint CreateIndexBuffer(const std::vector<uint32_t> indices) {
        GLuint bufferId;
        glGenBuffers(1, &bufferId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            indices.size()*sizeof(uint32_t),
            indices.data(),
            GL_STATIC_DRAW
        );
        return bufferId;
    }

    // Render data
    const std::vector<glm::vec3> screenSurfaceVertices = {
        glm::vec3(-1.0f, -1.0f, 0.0f),
        glm::vec3(-1.0f, 3.0f, 0.0f),
        glm::vec3(3.0f, -1.0f, 0.0f)
    };
    const std::vector<uint32_t> screenSurfaceIndices = {2, 1, 0};
    const float START_TIME = SDL_GetPerformanceCounter();
    GLfloat previousTick = 0;

    OpenGLPipeline::OpenGLPipeline(const std::string& shaderName) : 
        shaderProgramId(CreateShaderProgram(shaderName)),
        uniformLocationMVP(glGetUniformLocation(shaderProgramId, "mvp")),
        uniformLocationCounter(glGetUniformLocation(shaderProgramId, "counter")),
        uniformLocationiResolution(glGetUniformLocation(shaderProgramId, "iResolution")),
        attributeLocationVertexPosition(glGetAttribLocation(shaderProgramId, "vertexPosition")) {
        glUseProgram(shaderProgramId);
        const GLuint screenSurfaceVertexBufferId = CreateVertexBuffer(screenSurfaceVertices);
        const GLuint screenSurfaceIndexBufferId = CreateIndexBuffer(screenSurfaceIndices);
        glBindBuffer(GL_ARRAY_BUFFER, screenSurfaceVertexBufferId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, screenSurfaceIndexBufferId);
    }

    void OpenGLPipeline::Render(const glm::mat4& mvp) const {
        glUniformMatrix4fv(uniformLocationMVP, 1, GL_FALSE, &mvp[0][0]);
        GLfloat counter = (SDL_GetTicks())/1000.0;
        glUniform1fv(uniformLocationCounter, 1, &counter);
        GLfloat dt = counter - previousTick;
        previousTick = counter;
        GLfloat iResolution[2] = {
            static_cast<GLfloat>(GetDisplaySize().first),
            static_cast<GLfloat>(GetDisplaySize().second)
        };
        glUniform2fv(uniformLocationiResolution, 1, iResolution);
        glViewport(0, 0, static_cast<GLsizei>(iResolution[0]), static_cast<GLsizei>(iResolution[1]));

        glEnableVertexAttribArray(attributeLocationVertexPosition);
        glVertexAttribPointer(attributeLocationVertexPosition, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)0);
        glDisableVertexAttribArray(attributeLocationVertexPosition);
    }
    
    OpenGLPipeline::~OpenGLPipeline() {
        glDeleteProgram(shaderProgramId);
    }
}