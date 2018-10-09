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

#ifndef FIRESTORM_SHADER_HPP
#define FIRESTORM_SHADER_HPP

#include "Device.hpp"
#include "core/Types.hpp"

#include <memory>

namespace fs::graphics
{

enum class ShaderType
{
    Unknwon,
    Vertex,
    Fragment
};

class Shader
{
public:
    Shader() = default;
    virtual ~Shader() = default;

    void create(const Device& device, const std::vector<core::fs_int8>& code, ShaderType type);
    virtual void destroy();

    const VkShaderModule getShaderModule() const;

private:
    const Device* device = nullptr;

    ShaderType type = ShaderType::Unknwon;
    VkShaderModule shaderModule = VK_NULL_HANDLE;
};
typedef std::unique_ptr<Shader> ShaderPtr;
}

#endif //FIRESTORM_SHADER_HPP
