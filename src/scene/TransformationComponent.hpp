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

#ifndef FIRESTORM_TRANSFORMATIONCOMPONENT_HPP
#define FIRESTORM_TRANSFORMATIONCOMPONENT_HPP

#include "Component.hpp"
#include "core/Types.hpp"
#include "graphics/Transform.hpp"

#include <memory>

namespace fs::scene
{
class TransformationComponent : public Component
{
public:
    TransformationComponent() = default;
    virtual ~TransformationComponent() = default;

    void create(SceneNode& sceneNode);
    void destroy() override;

    core::Vector2f getPosition() const;
    virtual void setPosition(core::fs_float32 x, core::fs_float32 y);
    virtual void setPosition(core::Vector2f position);

    core::fs_float32 getLayer() const;
    void setLayer(core::fs_float32 layer);

    core::Vector3f getRotation() const;
    virtual void setRotation(core::fs_float32 rotation);
    virtual void setRotation(core::Vector3f rotation);

    core::Vector2f getScale() const;
    void setScale(core::fs_float32 x, core::fs_float32 y);
    void setScale(core::Vector2f scale);

    bool isTransformUpdated() const;
    void setTransformUpdated(bool geometryUpdated);

    void updateTransform();

    const graphics::Transform& getTransform() const;

protected:
    void calculateModelMatrix();

protected:
    graphics::Transform transform;

    core::Vector2f position;
    core::Vector3f rotation;
    core::fs_float32 layer = 0.f;
    core::Vector2f scale;
    bool transformUpdated = false;

};

typedef std::unique_ptr<TransformationComponent> TransformationComponentPtr;
}

#endif //FIRESTORM_TRANSFORMATIONCOMPONENT_HPP
