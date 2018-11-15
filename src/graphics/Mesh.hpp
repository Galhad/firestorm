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

#ifndef FIRESTORM_MESH_HPP
#define FIRESTORM_MESH_HPP

#include "vulkan/Vertex.hpp"
#include "core/Types.hpp"

#include <memory>
#include <vector>

namespace fs::graphics
{
class Mesh
{
public:
    Mesh() = default;
    virtual ~Mesh() = default;

    void create(const std::vector<graphics::Vertex>& vertices, const std::vector<core::fs_uint32>& indices);
    virtual void destroy();

    const std::vector<graphics::Vertex>& getVertices() const;
    void setVertices(const std::vector<graphics::Vertex>& vertices);

    const std::vector<core::fs_uint32>& getIndices() const;
    void setIndices(const std::vector<core::fs_uint32>& indices);

    core::fs_uint32 getIndexBase() const;
    void setIndexBase(core::fs_uint32 indexBase);

protected:
    std::vector<graphics::Vertex> vertices;
    std::vector<core::fs_uint32> indices;

    core::fs_uint32 indexBase = 0;
};

typedef std::unique_ptr<Mesh> MeshPtr;
}

#endif //FIRESTORM_MESH_HPP