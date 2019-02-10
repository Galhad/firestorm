


#include "RendererComponent.hpp"

namespace fs::scene
{

void RendererComponent::create(SceneNode& sceneNode, TransformationComponent& transformation)
{
    Component::create(sceneNode);
    RendererComponent::transformation = &transformation;
    active = true;
}

void RendererComponent::destroy()
{
    active = false;
    transformation = nullptr;
    Component::destroy();
}

void RendererComponent::pushTransform(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout)
{
    if (transformation->isTransformUpdated())
    {
        transformation->updateTransform();
    }

    vkCmdPushConstants(commandBuffer, pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(graphics::Transform),
                       &transformation->getTransform());
}

bool RendererComponent::isActive() const
{
    return active;
}

void RendererComponent::setActive(bool active)
{
    RendererComponent::active = active;
}

}
