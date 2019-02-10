


#ifndef FIRESTORM_SPRITERENDERERCOMPONENT_HPP
#define FIRESTORM_SPRITERENDERERCOMPONENT_HPP

#include "RendererComponent.hpp"
#include "graphics/Sprite.hpp"

#include <memory>

namespace fs::scene
{
class SpriteRendererComponent : public RendererComponent
{
public:
    SpriteRendererComponent() = default;
    ~SpriteRendererComponent() override = default;

    void create(SceneNode& sceneNode, TransformationComponent& transformation, const graphics::Sprite& sprite);
    void destroy() override;

    void
    render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, VkDescriptorSet sceneDescriptorSet) override;

    const graphics::Sprite* getSprite() const;
    void setSprite(const graphics::Sprite& sprite);

protected:
    const graphics::Sprite* sprite = nullptr;
};

typedef std::unique_ptr<SpriteRendererComponent> SpriteRendererComponentPtr;
}

#endif //FIRESTORM_SPRITERENDERERCOMPONENT_HPP
