


#ifndef FIRESTORM_WINDOWCREATIONPARAMS_HPP
#define FIRESTORM_WINDOWCREATIONPARAMS_HPP

#include "core/Types.hpp"

#include <string>

namespace fs::graphics
{
struct WindowCreationParams
{
    core::Vector2i windowSize = {800, 600};
    std::string windowTitle = "Firestorm";
    core::fs_uint32 windowFlags = 0;
};
}

#endif //FIRESTORM_WINDOWCREATIONPARAMS_HPP
