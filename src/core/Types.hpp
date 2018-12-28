// MIT License
//
// Copyright (c) 2018 Wojciech Wilk
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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

using Vector2f = glm::vec2;
using Vector3f = glm::vec3;
using Vector4f = glm::vec4;

using Quaternion = glm::quat;

using fs_float32 = float;
using fs_float64 = double;

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
