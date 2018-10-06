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

fs::Window::Window()
{

}

fs::Window::~Window()
{
    destroy();
}

void fs::Window::create(Vector2i size, const std::string& title, fs_uint32 flags)
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    window = glfwCreateWindow(static_cast<int>(size.x), static_cast<int>(size.y), title.c_str(), nullptr, nullptr);
}

void fs::Window::destroy()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWwindow* fs::Window::getWindow() const
{
    return window;
}

const std::string& fs::Window::getTitle() const
{
    return title;
}

void fs::Window::setTitle(std::string& title)
{
    this->title = title;
    glfwSetWindowTitle(window, title.c_str());
}

Vector2i fs::Window::getPosition() const
{
    Vector2i position{};
    glfwGetWindowPos(window, (int*) &position.x, (int*) &position.y);
    return position;
}

void fs::Window::setPosition(Vector2i position)
{
    glfwSetWindowPos(window, static_cast<int>(position.x), static_cast<int>(position.y));
}
