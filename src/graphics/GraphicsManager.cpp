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

#include "GraphicsManager.hpp"

#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>

#include <vector>
#include <set>

namespace fs::graphics
{
GraphicsManager::GraphicsManager() : window(new Window()), vulkanDriver(new VulkanDriver())
{

}

void GraphicsManager::create(const WindowCreationParams& windowCreationParams,
                             const GraphicsCreationParams& graphicsCreationParams)
{
    window->create(windowCreationParams.windowSize, windowCreationParams.windowTitle, windowCreationParams.windowFlags);
    vulkanDriver->create(graphicsCreationParams, *window);
}

void GraphicsManager::destroy()
{
    clearSpriteSheets();

    vulkanDriver->destroy();
    window->destroy();
}

SpriteSheet* GraphicsManager::createSpriteSheet(const io::Resource& resource, core::fs_uint32 pixelsPerUnit)
{
    int width, height, channels;
    int desiredChannels = STBI_rgb_alpha;
    const auto& bytes = resource.getData();
    stbi_uc* pixels = stbi_load_from_memory(bytes.data(), static_cast<int>(bytes.size()), &width, &height,
                                            &channels, desiredChannels);
    auto imageSize = static_cast<VkDeviceSize>(width * height * desiredChannels);

    if (!pixels)
    {
        throw std::runtime_error("Failed to load texture image!");
    }

    TextureImage textureImage;
    textureImage.create(vulkanDriver->getDevice(), static_cast<core::fs_uint32>(width),
                        static_cast<core::fs_uint32>(height),
                        pixels, imageSize);

    auto& spriteSheet = spriteSheets.emplace_back();
    spriteSheet.create(vulkanDriver->getGraphicsPipeline(), textureImage,
                       static_cast<core::fs_uint32>(width), static_cast<core::fs_uint32>(height),
                       pixelsPerUnit, static_cast<core::fs_uint32>(desiredChannels));

    stbi_image_free(pixels);

    return &spriteSheet;
}

void GraphicsManager::clearSpriteSheets()
{
    for (auto& spriteSheet : spriteSheets)
    {
        spriteSheet.destroy();
    }
    spriteSheets.clear();
}

void GraphicsManager::draw()
{
    bool spritesChanged = false;
    for (auto& spriteSheet : spriteSheets)
    {
        if (spriteSheet.areSpritesChanged())
        {
            spritesChanged = true;
            spriteSheet.setSpritesChanged(false);
        }
    }
    if (spritesChanged)
    {
        createVertexBuffers();
    }

    vulkanDriver->draw();
}

const Window& GraphicsManager::getWindow() const
{
    return *window;
}

Window& GraphicsManager::getWindow()
{
    return *window;
}

const VulkanDriver& GraphicsManager::getVulkanDriver() const
{
    return *vulkanDriver;
}

VulkanDriver& GraphicsManager::getVulkanDriver()
{
    return *vulkanDriver;
}

void GraphicsManager::createVertexBuffers()
{
    std::vector<Vertex> vertices;
    std::vector<core::fs_uint32> indices;
    core::fs_uint32 indexBase = 0;

    std::set<Sprite*> processedSprites;
    for (auto& spriteSheet : spriteSheets)
    {
        for (auto& sprite : spriteSheet.getSprites())
        {
            if (processedSprites.find(&sprite) != processedSprites.end())
            {
                continue;
            }

            auto& mesh = sprite.getMesh();
            mesh.setIndexBase(indexBase);

            vertices.insert(vertices.end(), mesh.getVertices().begin(), mesh.getVertices().end());
            indices.insert(indices.end(), mesh.getIndices().begin(), mesh.getIndices().end());

            indexBase += mesh.getVertices().size();
            processedSprites.insert(&sprite);
        }
    }

    vulkanDriver->createVertexBuffers(vertices, indices);
}

const std::list<SpriteSheet>& GraphicsManager::getSpriteSheets() const
{
    return spriteSheets;
}

}
