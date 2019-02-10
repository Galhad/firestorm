


#include "SpriteRendererComponent.hpp"

namespace fs::scene
{
void SpriteRendererComponent::create(SceneNode& sceneNode, TransformationComponent& transformation,
                                     const graphics::Sprite& sprite)
{
    RendererComponent::create(sceneNode, transformation);
    SpriteRendererComponent::sprite = &sprite;
}

void SpriteRendererComponent::destroy()
{
    sprite = nullptr;
    RendererComponent::destroy();
}

void SpriteRendererComponent::render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout,
                                     VkDescriptorSet sceneDescriptorSet)
{
    if (!active)
    {
        return;
    }

    pushTransform(commandBuffer, pipelineLayout);

    std::array<VkDescriptorSet, 2> descriptorSets = {sceneDescriptorSet, sprite->getDescriptorSet()};

    vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0,
                            static_cast<uint32_t>(descriptorSets.size()), descriptorSets.data(), 0, nullptr);

    vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(sprite->getMesh().getIndices().size()), 1, 0,
                     sprite->getMesh().getIndexBase(), 0);
}

const fs::graphics::Sprite* SpriteRendererComponent::getSprite() const
{
    return sprite;
}

void SpriteRendererComponent::setSprite(const fs::graphics::Sprite& sprite)
{
    SpriteRendererComponent::sprite = &sprite;
    transformation->setTransformUpdated(true);
}

}
