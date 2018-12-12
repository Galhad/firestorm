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

#include "Tile.hpp"

namespace fs::scene
{
Tile::Tile(Tile&& other) : id(other.id), sceneNode(std::move(other.sceneNode))
{
}

void Tile::create(core::fs_int32 id, SceneNode* sceneNode)
{
    Tile::id = id;
    Tile::sceneNode = SceneNodePtr(sceneNode);
}

void Tile::destroy()
{
    sceneNode = nullptr;
    id = -1;
}

core::fs_int32 Tile::getId() const
{
    return id;
}

void Tile::setId(core::fs_int32 id)
{
    Tile::id = id;
}

SceneNode* Tile::getSceneNode()
{
    return sceneNode.get();
}

const SceneNode* Tile::getSceneNode() const
{
    return sceneNode.get();
}

void Tile::setSceneNode(SceneNode* sceneNode)
{
    Tile::sceneNode = SceneNodePtr(sceneNode);
}

}
