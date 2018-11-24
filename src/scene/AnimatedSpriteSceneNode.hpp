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

    void create(const Animation& animation, core::fs_float32 speedFps = 1.f);
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
    core::fs_float32 elapsedTime;

};

typedef std::unique_ptr<AnimatedSpriteSceneNode> AnimatedSpriteSceneNodePtr;
}

#endif //FIRESTORM_ANIMATEDSPRITESCENENODE_HPP
