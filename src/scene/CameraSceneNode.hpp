


#ifndef FIRESTORM_CAMERASCENENODE_HPP
#define FIRESTORM_CAMERASCENENODE_HPP

#include "SceneNode.hpp"
#include "graphics/vulkan/MappedMemoryBuffer.hpp"
#include "graphics/UniformData.hpp"

#include <memory>

namespace fs::scene
{
class CameraSceneNode : public SceneNode
{
public:
    CameraSceneNode() = default;
    ~CameraSceneNode() override = default;

    void create(io::InputManager& inputManager, const graphics::Window& window,
                const graphics::MappedMemoryBuffer& uniformBuffer);
    void destroy() override;

    void update(float deltaTime) override;

    bool isActive() const;
    void setActive(bool active);

    core::fs_float32 getZoom() const;
    void setZoom(core::fs_float32 zoom);

    const graphics::Window* getWindow() const;
    void setWindow(const graphics::Window* window);

    void updateUniformData();

protected:
    bool active = false;
    const graphics::Window* window = nullptr;
    core::fs_float32 zoom = 10.f;

    const graphics::MappedMemoryBuffer* uniformBuffer = nullptr;

    graphics::UniformData uniformData = {};

};

typedef std::unique_ptr<CameraSceneNode> CameraSceneNodePtr;
}

#endif //FIRESTORM_CAMERASCENENODE_HPP
