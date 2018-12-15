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

	for(auto it = scenes.begin(); it != scenes.end();)
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
