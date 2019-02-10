


#ifndef FIRESTORM_SWAPCHAINSUPPORTDETAILS_HPP
#define FIRESTORM_SWAPCHAINSUPPORTDETAILS_HPP

#include <vulkan/vulkan.h>
#include <vector>

namespace fs::graphics
{
struct SwapChainSupportDetails
{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};
}

#endif //FIRESTORM_SWAPCHAINSUPPORTDETAILS_HPP
