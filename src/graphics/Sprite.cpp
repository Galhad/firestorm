


#include "Sprite.hpp"

namespace fs::graphics
{
void Sprite::create(core::Recti rect, const Texture& texture, const VkDescriptorSet& descriptorSet)
{
    Sprite::rect = rect;
    Sprite::texture = &texture;
    Sprite::descriptorSet = descriptorSet;

    createMesh();
}

void Sprite::createMesh()
{
    widthUnits = static_cast<core::fs_float32>(rect.width) / texture->getPixelsPerUnit();
    auto halfWidth = widthUnits / 2.f;
    heightUnits = static_cast<core::fs_float32>(rect.height) / texture->getPixelsPerUnit();
    auto halfHeight = heightUnits / 2.f;

    core::Rectf textureRect{};
    textureRect.x = static_cast<core::fs_float32>(rect.x) / texture->getWidthPixels();
    textureRect.y = static_cast<core::fs_float32>(rect.y) / texture->getHeightPixels();
    textureRect.width = static_cast<core::fs_float32>(rect.width) / texture->getWidthPixels();
    textureRect.height = static_cast<core::fs_float32>(rect.height) / texture->getHeightPixels();

    std::vector<Vertex> vertices;
    vertices.push_back({
                           {-halfWidth,    -halfHeight, 0.f},
                           {1.0f,          0.0f,        0.0f},
                           {textureRect.x, textureRect.y}
                       });
    vertices.push_back({
                           {halfWidth,                         -halfHeight, 0.f},
                           {0.0f,                              1.0f,        0.0f},
                           {textureRect.x + textureRect.width, textureRect.y}
                       });
    vertices.push_back({
                           {halfWidth,                         halfHeight, 0.f},
                           {0.0f,                              0.0f,       1.0f},
                           {textureRect.x + textureRect.width, textureRect.y + textureRect.height}
                       });
    vertices.push_back({
                           {-halfWidth,    halfHeight, 0.f},
                           {1.0f,          1.0f,       1.0f},
                           {textureRect.x, textureRect.y + textureRect.height}
                       });

    const std::vector<core::fs_uint32> indices{0, 1, 2, 2, 3, 0};

    mesh.create(vertices, indices);
}

void Sprite::destroy()
{
    destroyMesh();

    texture = nullptr;
    descriptorSet = VK_NULL_HANDLE;
}

void Sprite::destroyMesh()
{
    mesh.destroy();
}

const VkDescriptorSet Sprite::getDescriptorSet() const
{
    return descriptorSet;
}

const Texture* Sprite::getTexture() const
{
    return texture;
}

Mesh& Sprite::getMesh()
{
    return mesh;
}

const Mesh& Sprite::getMesh() const
{
    return mesh;
}

core::fs_float32 Sprite::getWidthUnits() const
{
    return widthUnits;
}

core::fs_float32 Sprite::getHeightUnits() const
{
    return heightUnits;
}
}
