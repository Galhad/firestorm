


#ifndef FIRESTORM_RENDERERCOMPONENT_HPP
#define FIRESTORM_RENDERERCOMPONENT_HPP

#include "Component.hpp"
#include "graphics/Sprite.hpp"
#include "graphics/vulkan/Vertex.hpp"
#include "TransformationComponent.hpp"

#include <memory>

namespace fs::scene
{
class RendererComponent : public Component
{
public:
    RendererComponent() = default;
    ~RendererComponent() override = default;

    void create(SceneNode& sceneNode, TransformationComponent& transformation);
    void destroy() override;

    virtual void
    render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, VkDescriptorSet sceneDescriptorSet) = 0;

    bool isActive() const;
    void setActive(bool active);

protected:
    void pushTransform(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout);

protected:
    TransformationComponent* transformation = nullptr;
    bool active = true;

};

typedef std::unique_ptr<RendererComponent> RendererComponentPtr;
}

#endif //FIRESTORM_RENDERERCOMPONENT_HPP
