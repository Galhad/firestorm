


#include "Mesh.hpp"

namespace fs::graphics
{

void Mesh::create(const std::vector<graphics::Vertex>& vertices, const std::vector<core::fs_uint32>& indices)
{
    setVertices(vertices);
    setIndices(indices);
}

void Mesh::destroy()
{

}

const std::vector<graphics::Vertex>& Mesh::getVertices() const
{
    return vertices;
}

void Mesh::setVertices(const std::vector<graphics::Vertex>& vertices)
{
    Mesh::vertices = vertices;
}

const std::vector<core::fs_uint32>& Mesh::getIndices() const
{
    return indices;
}

void Mesh::setIndices(const std::vector<core::fs_uint32>& indices)
{
    Mesh::indices = indices;
}

core::fs_uint32 Mesh::getIndexBase() const
{
    return indexBase;
}

void Mesh::setIndexBase(core::fs_uint32 indexBase)
{
    Mesh::indexBase = indexBase;
}
}
