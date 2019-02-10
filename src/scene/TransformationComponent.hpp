


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
