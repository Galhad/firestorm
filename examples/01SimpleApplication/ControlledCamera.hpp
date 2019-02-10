#ifndef FIRESTORM_CONTROLLEDCAMERA_HPP
#define FIRESTORM_CONTROLLEDCAMERA_HPP

#include "scene/CameraSceneNode.hpp"

#include <memory>

namespace fs
{
class ControlledCamera : public scene::CameraSceneNode
{
public:
    ControlledCamera() = default;
    ~ControlledCamera() override = default;

    void create(io::InputManager& inputManager, const graphics::Window& window,
                const graphics::MappedMemoryBuffer& uniformBuffer);
    void destroy() override;

    void update(float deltaTime) override;

protected:
    float cameraSpeed = 10.f;

};

typedef std::unique_ptr<ControlledCamera> ControlledCameraPtr;

}

#endif //FIRESTORM_CONTROLLEDCAMERA_HPP
