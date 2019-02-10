


#ifndef FIRESTORM_ANIMATEDSPRITESCENENODE_HPP
#define FIRESTORM_ANIMATEDSPRITESCENENODE_HPP

#include "SpriteSceneNode.hpp"

#include <memory>
#include <vector>

namespace fs::scene
{
class AnimatedSpriteSceneNode : public SpriteSceneNode
{
public:
    using Animation = std::vector<const graphics::Sprite*>;

public:
    AnimatedSpriteSceneNode() = default;
    virtual ~AnimatedSpriteSceneNode() = default;

    void create(io::InputManager& inputManager, const Animation& animation, core::fs_float32 speedFps = 1.f);
    void destroy() override;

    void update(float deltaTime) override;

    const Animation& getAnimation() const;
    void setAnimation(const Animation& animation);

    core::fs_uint32 getCurrentFrame() const;
    void setCurrentFrame(core::fs_uint32 currentFrame);

    core::fs_float32 getSpeedFps() const;
    void setSpeedFps(core::fs_float32 speedFps);

protected:
    const Animation* animation = nullptr;
    core::fs_uint32 currentFrame;
    core::fs_float32 speedFps;
    core::fs_float32 frameTime;
    core::fs_float32 elapsedTime;

};

typedef std::unique_ptr<AnimatedSpriteSceneNode> AnimatedSpriteSceneNodePtr;
}

#endif //FIRESTORM_ANIMATEDSPRITESCENENODE_HPP
