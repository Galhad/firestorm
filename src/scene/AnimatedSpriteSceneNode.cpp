


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
