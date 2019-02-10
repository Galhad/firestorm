


#include "Component.hpp"

namespace fs::scene
{

void Component::create(SceneNode& sceneNode)
{
    Component::sceneNode = &sceneNode;
}

void Component::destroy()
{
    sceneNode = nullptr;
}

SceneNode* Component::getSceneNode() const
{
    return sceneNode;
}

void Component::setSceneNode(SceneNode& sceneNode)
{
    Component::sceneNode = &sceneNode;
}
}
