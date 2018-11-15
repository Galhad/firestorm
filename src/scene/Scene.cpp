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

#include "graphics/vulkan/CommandBuffer.hpp"
#include "Scene.hpp"
#include "graphics/vulkan/Vertex.hpp"

#include <algorithm>
#include <set>

namespace fs::scene
{

void Scene::create(/*const graphics::VulkanDriver& driver*/)
{
//    Scene::driver = &driver;

//    std::vector<VkWriteDescriptorSet> writeDescriptorSets;
//    writeDescriptorSets.push_back(vks::initializers::writeDescriptorSet(
//        sceneDescriptorSet,
//        VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
//        0,
//        &uniformBuffer.descriptor));
//
//    vkUpdateDescriptorSets(device->logicalDevice, static_cast<uint32_t>(writeDescriptorSets.size()), writeDescriptorSets.data(), 0, NULL);
}

void Scene::destroy()
{
//    driver = nullptr;

    name.clear();
    nodes.clear();

//    vertexBuffer.destroy();
//    indexBuffer.destroy();
}

void Scene::update(float deltaTime)
{
    for (auto& node : nodes)
    {
        node->update(deltaTime);
    }
}

void Scene::render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, VkDescriptorSet sceneDescriptorSet)
{
//    VkDeviceSize offsets[1] = {0};
//
//    // Bind scene vertex and index buffers
//    vkCmdBindVertexBuffers(commandBuffer, 0, 1, &vertexBuffer.getBuffer(), offsets);
//    vkCmdBindIndexBuffer(commandBuffer, indexBuffer.getBuffer(), 0, VK_INDEX_TYPE_UINT32);

    for (auto& node : nodes)
    {
        node->render(commandBuffer, pipelineLayout, sceneDescriptorSet);
    }
}

//void Scene::createBuffers()
//{
//    std::vector<graphics::Vertex> vertices;
//    std::vector<core::fs_uint32> indices;
//    core::fs_uint32 indexBase = 0;
//
//    std::set<graphics::Material*> processedMaterials;
//    for (auto& node : nodes)
//    {
//        graphics::Material* material = node->getMaterial();
//
//        if(material == nullptr || processedMaterials.find(material) != processedMaterials.end())
//        {
//            continue;
//        }
//
//        auto& mesh = material->getMesh();
//        mesh.setIndexBase(indexBase);
//
//        vertices.insert(vertices.end(), mesh.getVertices().begin(), mesh.getVertices().end());
//        indices.insert(indices.end(), mesh.getIndices().begin(), mesh.getIndices().end());
//
//        indexBase += mesh.getVertices().size();
//        processedMaterials.insert(material);
//    }
//
//    // Create buffers
//    // For better performance we only create one index and vertex buffer to keep number of memory allocations down
//    size_t vertexDataSize = vertices.size() * sizeof(graphics::Vertex);
//    size_t indexDataSize = indices.size() * sizeof(core::fs_uint32);
//
//    graphics::Buffer vertexStaging;
//    vertexStaging.create(driver->getDevice(), static_cast<uint32_t>(vertexDataSize), VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
//                         VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, vertices.data());
//
//    vertexBuffer.create(driver->getDevice(), static_cast<uint32_t>(vertexDataSize),
//                        VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
//                        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
//
//    graphics::Buffer indexStaging;
//    indexStaging.create(driver->getDevice(), static_cast<uint32_t>(indexDataSize), VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
//                        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, indices.data());
//
//    indexBuffer.create(driver->getDevice(), static_cast<uint32_t>(indexDataSize),
//                       VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
//                       VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
//
//    graphics::CommandBuffer commandBuffer;
//    commandBuffer.create(driver->getDevice());
//    commandBuffer.beginSingleTimeCommand();
//
//    VkBufferCopy copyRegion = {};
//
//    copyRegion.size = vertexDataSize;
//    vkCmdCopyBuffer(
//        commandBuffer.getCommandBuffer(),
//        vertexStaging.getBuffer(),
//        vertexBuffer.getBuffer(),
//        1,
//        &copyRegion);
//
//    copyRegion.size = indexDataSize;
//    vkCmdCopyBuffer(
//        commandBuffer.getCommandBuffer(),
//        indexStaging.getBuffer(),
//        indexBuffer.getBuffer(),
//        1,
//        &copyRegion);
//
//    commandBuffer.endSingleTimeCommand();
//
//    vertexStaging.destroy();
//    indexStaging.destroy();
//}

const std::vector<SceneNode*>& Scene::getNodes() const
{
    return nodes;
}

std::vector<SceneNode*>& Scene::getNodes()
{
    return nodes;
}

}
