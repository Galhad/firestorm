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

#ifndef FIRESTORM_INPUTMANAGER_HPP
#define FIRESTORM_INPUTMANAGER_HPP

#include "Keys.hpp"
#include "core/Types.hpp"
#include "graphics/Window.hpp"

#include <memory>

namespace fs::io
{
class InputManager
{
public:
    InputManager();
    virtual ~InputManager() = default;

    void create(const graphics::Window& window);
    void destroy();

    KeyState getKeyState(Key key) const;
    KeyState getButtonState(Button button) const;

protected:
    const graphics::Window* window;

};

typedef std::unique_ptr<InputManager> InputManagerPtr;
}

#endif //FIRESTORM_INPUTMANAGER_HPP
