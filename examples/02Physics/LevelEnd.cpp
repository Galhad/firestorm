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

#include "LevelEnd.hpp"
#include "Labels.hpp"

namespace fs::scene
{
void LevelEnd::create(io::InputManager& inputManager, fs::physics::PhysicsManager& physicsManager, const core::Vector2f& point1,
                      const core::Vector2f& point2)
{
    SceneNode::create(inputManager);

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;

    b2EdgeShape shape;
    shape.Set(b2Vec2(point1.x, point1.y), b2Vec2(point2.x, point2.y));

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;

    createBodyComponent(physicsManager, bodyDef, fixtureDef);

    labels.insert(LABEL_LEVEL_END);
}

void LevelEnd::destroy()
{
    SceneNode::destroy();
}
}
