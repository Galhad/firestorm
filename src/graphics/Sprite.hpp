


#ifndef FIRESTORM_SPRITE_HPP
#define FIRESTORM_SPRITE_HPP

#include "Texture.hpp"
#include "Mesh.hpp"
#include "vulkan/GraphicsPipeline.hpp"

#include <memory>

namespace fs::graphics
{
class Sprite
{
public:
    Sprite() = default;
    virtual ~Sprite() = default;

    void create(core::Recti rect, const Texture& texture, const VkDescriptorSet& descriptorSet);
    virtual void destroy();

    const Texture* getTexture() const;
    const VkDescriptorSet getDescriptorSet() const;

    Mesh& getMesh();
    const Mesh& getMesh() const;

    core::fs_float32 getWidthUnits() const;
    core::fs_float32 getHeightUnits() const;

private:
    void createMesh();
    void destroyMesh();

private:
    Mesh mesh;

    core::Recti rect;
    const Texture* texture = nullptr;

    core::fs_float32 widthUnits = 0.f;
    core::fs_float32 heightUnits = 0.f;

    VkDescriptorSet descriptorSet = VK_NULL_HANDLE;

};

typedef std::unique_ptr<Sprite> SpritePtr;
}

#endif //FIRESTORM_SPRITE_HPP
