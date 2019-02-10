


#ifndef FIRESTORM_WINDOW_HPP
#define FIRESTORM_WINDOW_HPP

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

#include "core/Types.hpp"

#include <string>
#include <functional>
#include <memory>

namespace fs::graphics
{

using WindowResizedCallback =
std::function< void(core::fs_int32
width,
core::fs_int32 height
)>;

class Window
{
public:
    Window() = default;
    virtual ~Window();

    void create(core::Vector2i size, const std::string& title, core::fs_uint32 flags = 0);
    virtual void destroy();

    const std::string& getTitle() const;
    void setTitle(std::string& title);

    core::Vector2i getPosition() const;
    void setPosition(core::Vector2i position);

    const core::Vector2i& getSize() const;

    GLFWwindow* getWindow() const;

    const WindowResizedCallback& getWindowResizedCallback() const;
    void setWindowResizedCallback(const WindowResizedCallback& windowResizedCallback);

protected:
    void onWindowResized(core::fs_int32 width, core::fs_int32 height);

protected:
    GLFWwindow* window = nullptr;
    std::string title;
    core::Vector2i size;

    WindowResizedCallback windowResizedCallback = {};
};

typedef std::unique_ptr<Window> WindowPtr;
}

#endif //FIRESTORM_WINDOW_HPP
