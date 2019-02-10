


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
