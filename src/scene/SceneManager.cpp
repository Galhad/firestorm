


#include "SceneManager.hpp"

namespace fs::scene
{

void SceneManager::create()
{

}

void SceneManager::destroy()
{
    activeScene = nullptr;
    clearScenes();
}

Scene* SceneManager::createScene()
{
    ScenePtr scene(new Scene());

    auto result = scenes.insert(std::move(scene));
    if (!result.second)
    {
        return nullptr;
    }

    return result.first->get();
}

void SceneManager::destroyScene(const Scene* scene)
{
    for (const auto& ownedScene : scenes)
    {
        if (ownedScene.get() == scene)
        {
            if (activeScene == scene)
            {
                activeScene = nullptr;
            }

            ownedScene->destroy();
            scenes.erase(ownedScene);
            break;
        }
    }
}

void SceneManager::clearScenes()
{
    activeScene = nullptr;

    for (auto it = scenes.begin(); it != scenes.end();)
    {
        (*it)->destroy();
        it = scenes.erase(it);
    }
}

void SceneManager::setActiveScene(const Scene* activeScene)
{
    for (const auto& scene : scenes)
    {
        if (scene.get() == activeScene)
        {
            this->activeScene = scene.get();
        }
    }
}

Scene* SceneManager::getActiveScene() const
{
    return activeScene;
}
}
