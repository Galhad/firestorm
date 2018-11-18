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
    ~CameraSceneNode() override;

    void create(const graphics::Window& window, const graphics::MappedMemoryBuffer& uniformBuffer);
    void destroy() override;

    void setPosition(core::fs_float32 x, core::fs_float32 y) override;
    void setPosition(core::Vector2f position) override;
    void setRotation(core::fs_float32 rotation) override;
    void setRotation(core::Vector3f rotation) override;

    void update(float deltaTime) override;
    virtual void
    render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, VkDescriptorSet scenedescriptorSet) override;

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
