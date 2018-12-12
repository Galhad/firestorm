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
std::function<void(core::fs_int32
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
