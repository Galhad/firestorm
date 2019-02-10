


#include "graphics/vulkan/CommandBuffer.hpp"
#include "Scene.hpp"

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
