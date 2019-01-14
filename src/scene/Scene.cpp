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

void Scene::create()
{
    nodesModified = true;
}

void Scene::destroy()
{
    name.clear();
    nodes.clear();
}

void Scene::update(float deltaTime)
{
    for (auto& node : nodes)
    {
        node->update(deltaTime);
    }
}

void Scene::physicsUpdate()
{
    for (auto& node : nodes)
    {
        node->physicsUpdate();
    }
}

void Scene::applyPhysicsStep()
{
    for (auto& node : nodes)
    {
        node->applyPhysicsStep();
    }
}

void Scene::render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, VkDescriptorSet sceneDescriptorSet)
{
    for (auto& node : nodes)
    {
        auto* renderer = node->getRenderer();
        if (renderer != nullptr)
        {
            renderer->render(commandBuffer, pipelineLayout, sceneDescriptorSet);
        }
    }

    nodesModified = false;
}

const std::vector<SceneNode*>& Scene::getNodes() const
{
    return nodes;
}

std::vector<SceneNode*>& Scene::getNodes()
{
    return nodes;
}

CameraSceneNode* Scene::getActiveCamera()
{
    return activeCamera;
}

void Scene::setActiveCamera(CameraSceneNode* activeCamera)
{
    // todo: check if activeCamera is managed by this scene (contained in nodes)

    if (Scene::activeCamera != nullptr)
    {
        Scene::activeCamera->setActive(false);
    }

    Scene::activeCamera = activeCamera;
    activeCamera->setActive(true);
}

bool Scene::isTransformUpdated() const
{
    if (nodesModified)
    {
        return true;
    }

    for (auto& node : nodes)
    {
        if (node->getTransformation().isTransformUpdated())
        {
            return true;
        }
    }
    return false;
}

void Scene::addSceneNode(SceneNode& sceneNode)
{
    nodes.push_back(&sceneNode);
    sceneNode.setScene(this);
    nodesModified = true;
}

void Scene::removeSceneNode(SceneNode& sceneNode)
{
    for (auto it = nodes.begin(); it != nodes.end(); it++)
    {
        if (*it == &sceneNode)
        {
            nodes.erase(it);
        }
    }

    sceneNode.setScene(nullptr);
    nodesModified = true;
}

}
