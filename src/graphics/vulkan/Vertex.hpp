


#ifndef FIRESTORM_VERTEX_HPP
#define FIRESTORM_VERTEX_HPP

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>

#include <array>

namespace fs::graphics
{
struct Vertex
{
    glm::vec3 pos;
    glm::vec3 color;
    glm::vec2 texCoord;

    static VkVertexInputBindingDescription getBindingDescription();
    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions();
};

}
#endif //FIRESTORM_VERTEX_HPP
