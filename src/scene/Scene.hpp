


#ifndef FIRESTORM_SCENE_HPP
#define FIRESTORM_SCENE_HPP

#include "SceneNode.hpp"
#include "CameraSceneNode.hpp"

#include <memory>

namespace fs::scene
{
class Scene
{
public:
    Scene() = default;
    virtual ~Scene() = default;

    void create();
    virtual void destroy();

    void update(float deltaTime);
    void physicsUpdate();
    void render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, VkDescriptorSet sceneDescriptorSet);
    void applyPhysicsStep();

    const std::vector<SceneNode*>& getNodes() const;
    std::vector<SceneNode*>& getNodes();

    void addSceneNode(SceneNode& sceneNode);
    void removeSceneNode(SceneNode& sceneNode);

    CameraSceneNode* getActiveCamera();
    void setActiveCamera(CameraSceneNode* activeCamera);

    bool isTransformUpdated() const;

protected:
    std::string name;
    std::vector<SceneNode*> nodes;
    CameraSceneNode* activeCamera = nullptr;
    bool nodesModified = true;

};

typedef std::unique_ptr<Scene> ScenePtr;
}

#endif //FIRESTORM_SCENE_HPP
