


#ifndef FIRESTORM_TYPES_HPP
#define FIRESTORM_TYPES_HPP

#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <cstdint>

namespace fs::core
{
using fs_uint8 = uint8_t;
using fs_int8 = int8_t;

using fs_uint16 = uint16_t;
using fs_int16 = int16_t;

using fs_uint32 = uint32_t;
using fs_int32 = int32_t;

using fs_uint64 = uint64_t;
using fs_int64 = int64_t;

using fs_float32 = float;
using fs_float64 = double;

using Vector2f = glm::vec2;
using Vector3f = glm::vec3;
using Vector4f = glm::vec4;

using Quaternion = glm::quat;

using fs_mat4 = glm::mat4;
using fs_mat3 = glm::mat3;

struct Recti
{
    fs_uint64 x = 0;
    fs_uint64 y = 0;
    fs_uint64 width = 0;
    fs_uint64 height = 0;
};

struct Rectf
{
    fs_float32 x = 0.f;
    fs_float32 y = 0.f;
    fs_float32 width = 0.f;
    fs_float32 height = 0.f;
};

struct Vector2i
{
    fs_int64 x = 0ull;
    fs_int64 y = 0ull;
};

struct Vector2d
{
    double x = 0.;
    double y = 0.;
};

}

#endif //FIRESTORM_TYPES_HPP
