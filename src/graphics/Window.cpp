


#include "Window.hpp"

namespace fs::graphics
{
Window::~Window()
{
    destroy();
}

void Window::create(core::Vector2i size, const std::string& title, core::fs_uint32 flags)
{
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    window = glfwCreateWindow(static_cast<int>(size.x), static_cast<int>(size.y), title.c_str(), nullptr, nullptr);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)
    {
        auto fsWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        fsWindow->onWindowResized(width, height);
    });
    Window::size = size;
}

void Window::destroy()
{
    glfwDestroyWindow(window);
}

GLFWwindow* Window::getWindow() const
{
    return window;
}

const std::string& Window::getTitle() const
{
    return title;
}

void Window::setTitle(std::string& title)
{
    this->title = title;
    glfwSetWindowTitle(window, title.c_str());
}

core::Vector2i Window::getPosition() const
{
    core::Vector2i position{};
    glfwGetWindowPos(window, (int*) &position.x, (int*) &position.y);
    return position;
}

void Window::setPosition(core::Vector2i position)
{
    glfwSetWindowPos(window, static_cast<int>(position.x), static_cast<int>(position.y));
}

const core::Vector2i& Window::getSize() const
{
    return size;
}

void Window::onWindowResized(core::fs_int32 width, core::fs_int32 height)
{
    size.x = static_cast<core::fs_uint64>(width);
    size.y = static_cast<core::fs_uint64>(height);

    windowResizedCallback(width, height);
}

const WindowResizedCallback& Window::getWindowResizedCallback() const
{
    return windowResizedCallback;
}

void Window::setWindowResizedCallback(const WindowResizedCallback& windowResizedCallback)
{
    Window::windowResizedCallback = windowResizedCallback;
}

}
