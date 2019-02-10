


#include "TileMapRendererComponent.hpp"

namespace fs::scene
{
void TileMapRendererComponent::create(TileMapSceneNode& tileMap,
                                      TransformationComponent& transformation)
{
    RendererComponent::create(tileMap, transformation);
}

void TileMapRendererComponent::destroy()
{

    RendererComponent::destroy();
}

void TileMapRendererComponent::render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout,
                                      VkDescriptorSet sceneDescriptorSet)
{
    auto* tileMap = dynamic_cast<TileMapSceneNode*>(sceneNode);

    if (tileMap->isTilesChanged())
    {
        tileMap->buildTiles();
    }

    if (transformation->isTransformUpdated())
    {
        tileMap->updateTilesPosition();
    }

    for (auto& tileColumn : tileMap->getTiles())
    {
        for (auto& tile : tileColumn)
        {
            auto sceneNode = tile.getSceneNode();
            if (sceneNode != nullptr && sceneNode->getRenderer() != nullptr)
            {
                sceneNode->getRenderer()->render(commandBuffer, pipelineLayout, sceneDescriptorSet);
            }
        }
    }
}

}
