


#ifndef FIRESTORM_SWAPCHAIN_HPP
#define FIRESTORM_SWAPCHAIN_HPP

#include "Device.hpp"

#include <vulkan/vulkan.h>
#include <memory>
#include <vector>

namespace fs::graphics
{

class SwapChain
{
public:
    SwapChain() = default;
    virtual ~ SwapChain() = default;

    void create(const Device& device);
    virtual void destroy();

    const Device* getDevice() const;
    const VkSwapchainKHR getSwapChain() const;
    const std::vector<VkImage>& getSwapChainImages() const;
    VkFormat getSwapChainImageFormat() const;
    const VkExtent2D& getSwapChainExtent() const;
    const std::vector<VkImageView>& getSwapChainImageViews() const;

private:
    const Device* device = nullptr;

    VkSwapchainKHR swapChain = VK_NULL_HANDLE;
    VkSwapchainKHR oldSwapChain = VK_NULL_HANDLE;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat = VK_FORMAT_UNDEFINED;
    VkExtent2D swapChainExtent = {};
    std::vector<VkImageView> swapChainImageViews;

private:
    void createSwapChain();
    void destroy(VkSwapchainKHR swapchain);

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(std::vector<VkSurfaceFormatKHR> availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) const;
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) const;
    void createImageViews();
    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlagBits aspectFlags);
};

typedef std::unique_ptr<SwapChain> SwapChainPtr;

}

#endif //FIRESTORM_SWAPCHAIN_HPP
