


#include "Vertex.hpp"

namespace fs::graphics
{
VkVertexInputBindingDescription Vertex::getBindingDescription()
{
    VkVertexInputBindingDescription vertexInputBindingDescription = {};
    vertexInputBindingDescription.binding = 0;
    vertexInputBindingDescription.stride = sizeof(Vertex);
    vertexInputBindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    return vertexInputBindingDescription;
}

std::array<VkVertexInputAttributeDescription, 3> fs::graphics::Vertex::getAttributeDescriptions()
{
    std::array<VkVertexInputAttributeDescription, 3> attributeDescription = {};

    attributeDescription[0].binding = 0;
    attributeDescription[0].location = 0;
    attributeDescription[0].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributeDescription[0].offset = static_cast<uint32_t>(offsetof(Vertex, pos));

    attributeDescription[1].binding = 0;
    attributeDescription[1].location = 1;
    attributeDescription[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributeDescription[1].offset = static_cast<uint32_t>(offsetof(Vertex, color));

    attributeDescription[2].binding = 0;
    attributeDescription[2].location = 2;
    attributeDescription[2].format = VK_FORMAT_R32G32_SFLOAT;
    attributeDescription[2].offset = static_cast<uint32_t>(offsetof(Vertex, texCoord));

    return attributeDescription;
}
}
