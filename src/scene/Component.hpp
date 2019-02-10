


#ifndef FIRESTORM_COMPONENT_HPP
#define FIRESTORM_COMPONENT_HPP

#include <memory>

namespace fs::scene
{
class SceneNode;

class Component
{
public:
    Component() = default;
    virtual ~Component() = default;

    void create(SceneNode& sceneNode);
    virtual void destroy();

    SceneNode* getSceneNode() const;
    void setSceneNode(SceneNode& sceneNode);

protected:
    SceneNode* sceneNode = nullptr;

};

typedef std::unique_ptr<Component> ComponentPtr;
}

#endif //FIRESTORM_COMPONENT_HPP
