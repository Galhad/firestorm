


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
