// MIT License
//
// Copyright (c) 2018 Wojciech Wilk
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
