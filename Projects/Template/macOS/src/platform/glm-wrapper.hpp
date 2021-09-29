#pragma once

#define GLM_LANG_STL11_FORCED // fails to use c++11 extensions on android without this
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/hash.hpp> // might not need this since I'm not using meshes