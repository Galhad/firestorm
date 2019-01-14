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

#ifndef FIRESTORM_SPRITESCENENODE_HPP
#define FIRESTORM_SPRITESCENENODE_HPP

#include "SceneNode.hpp"
#include "SpriteRendererComponent.hpp"

#include <memory>

namespace fs::scene
{
class SpriteSceneNode : public SceneNode
{
public:
    SpriteSceneNode() = default;
    ~SpriteSceneNode() override = default;

    void create(io::InputManager& inputManager, const graphics::Sprite& sprite);
    void destroy() override;

};

typedef std::unique_ptr<SpriteSceneNode> SpriteSceneNodePtr;
}

#endif //FIRESTORM_SPRITESCENENODE_HPP
