


#ifndef FIRESTORM_TILEMAPRENDERERCOMPONENT_HPP
#define FIRESTORM_TILEMAPRENDERERCOMPONENT_HPP


#include "TileMapSceneNode.hpp"

#include "RendererComponent.hpp"

#include <memory>

namespace fs::scene
{

class TileMapRendererComponent : public RendererComponent
{
public:
    TileMapRendererComponent() = default;
    ~TileMapRendererComponent() override = default;

    void create(TileMapSceneNode& tileMap, TransformationComponent& transformation);
    void destroy() override;

    void
    render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, VkDescriptorSet sceneDescriptorSet) override;

};

typedef std::unique_ptr<TileMapRendererComponent> TileMapRendererComponentPtr;
}

#endif //FIRESTORM_TILEMAPRENDERERCOMPONENT_HPP
