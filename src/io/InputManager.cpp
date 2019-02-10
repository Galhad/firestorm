


#include "InputManager.hpp"

namespace fs::io
{
InputManager::InputManager() : window(nullptr)
{

}

void InputManager::create(const fs::graphics::Window& window)
{
    this->window = &window;
}

void InputManager::destroy()
{
    window = nullptr;
}

KeyState InputManager::getKeyState(Key key) const
{
    int state = glfwGetKey(window->getWindow(), static_cast<int>(key));
    return static_cast<KeyState>(state);
}

KeyState InputManager::getButtonState(Button button) const
{
    int state = glfwGetMouseButton(window->getWindow(), static_cast<int>(button));
    return static_cast<KeyState>(state);
}

}
