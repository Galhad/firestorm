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
}
