


#ifndef FIRESTORM_GRAPHICSCREATIONPARAMS_HPP
#define FIRESTORM_GRAPHICSCREATIONPARAMS_HPP

#include "core/Types.hpp"

#include <string>

namespace fs::graphics
{

struct GraphicsCreationParams
{
    std::string applicationName = "";
    core::fs_uint8 applicationVersionMajor = 0;
    core::fs_uint8 applicationVersionMinor = 0;
    core::fs_uint8 applicationVersionPath = 0;
    bool enableValidationLayers = false;
    core::fs_uint8 maxFramesInFlight = 2;
    core::fs_uint32 pixelsToUnits = 100;
};

}

#endif //FIRESTORM_GRAPHICSCREATIONPARAMS_HPP
