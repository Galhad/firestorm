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

#ifndef FIRESTORM_SIMPLEAPPLICATION_HPP
#define FIRESTORM_SIMPLEAPPLICATION_HPP


#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Engine.hpp>

#include <scene/SpriteSceneNode.hpp>
#include <scene/Camera.hpp>
#include <iostream>
#include <memory>

namespace fs
{
class SimpleApplication : public fs::Engine
{
public:
    SimpleApplication();
    ~SimpleApplication() override;

    void update(float deltaTimeMs) override;

private:
    scene::Camera camera;
    scene::Scene* scene;
    scene::SpriteSceneNode spriteSceneNode1;
    scene::SpriteSceneNode spriteSceneNode2;
    graphics::SpriteSheet* spriteSheet;
    graphics::Sprite* sprite;

};
typedef std::unique_ptr<SimpleApplication> SimpleApplicationPtr;
}

#endif //FIRESTORM_SIMPLEAPPLICATION_HPP