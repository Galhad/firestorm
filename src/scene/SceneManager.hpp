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
    void destoryScene(const Scene* scene);
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
