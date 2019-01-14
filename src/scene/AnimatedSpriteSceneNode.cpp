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

#include "AnimatedSpriteSceneNode.hpp"

namespace fs::scene
{
void
AnimatedSpriteSceneNode::create(io::InputManager& inputManager, const AnimatedSpriteSceneNode::Animation& animation,
                                core::fs_float32 speedFps)
{
    SpriteSceneNode::create(inputManager, *animation.front());
    AnimatedSpriteSceneNode::animation = &animation;
    currentFrame = 0;
    setSpeedFps(speedFps);
    elapsedTime = 0.f;
}

void AnimatedSpriteSceneNode::destroy()
{
    animation = nullptr;
    currentFrame = 0;
    SpriteSceneNode::destroy();
}

void AnimatedSpriteSceneNode::update(float deltaTime)
{
    elapsedTime += deltaTime;
    if (elapsedTime >= frameTime)
    {
        ++currentFrame;
        if (currentFrame >= animation->size())
        {
            currentFrame = 0;
        }

        dynamic_cast<SpriteRendererComponent*>(renderer.get())->setSprite(*animation->at(currentFrame));
        elapsedTime -= frameTime;
    }

    SpriteSceneNode::update(deltaTime);
}

const AnimatedSpriteSceneNode::Animation& AnimatedSpriteSceneNode::getAnimation() const
{
    return *animation;
}

void AnimatedSpriteSceneNode::setAnimation(const AnimatedSpriteSceneNode::Animation& animation)
{
    AnimatedSpriteSceneNode::animation = &animation;
    currentFrame = 0;
    elapsedTime = 0.f;
}

core::fs_uint32 AnimatedSpriteSceneNode::getCurrentFrame() const
{
    return currentFrame;
}

void AnimatedSpriteSceneNode::setCurrentFrame(core::fs_uint32 currentFrame)
{
    AnimatedSpriteSceneNode::currentFrame = currentFrame;
}

core::fs_float32 AnimatedSpriteSceneNode::getSpeedFps() const
{
    return speedFps;
}

void AnimatedSpriteSceneNode::setSpeedFps(core::fs_float32 speedFps)
{
    AnimatedSpriteSceneNode::speedFps = speedFps;
    frameTime = 1 / speedFps;
}

}
