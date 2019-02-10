


#ifndef FIRESTORM_SCENEMANAGER_HPP
#define FIRESTORM_SCENEMANAGER_HPP

#include "Scene.hpp"

#include <memory>
#include <set>

namespace fs::scene
{
class SceneManager
{
public:
    SceneManager() = default;
    virtual ~SceneManager() = default;

    void create();
    virtual void destroy();

    Scene* createScene();
    void destroyScene(const Scene* scene);
    void clearScenes();

    void setActiveScene(const Scene* activeScene);
    Scene* getActiveScene() const;

private:
    std::set<ScenePtr> scenes;
    Scene* activeScene = nullptr;

};

typedef std::unique_ptr<SceneManager> SceneManagerPtr;
}

#endif //FIRESTORM_SCENEMANAGER_HPP
