


#ifndef FIRESTORM_DEVICE_HPP
#define FIRESTORM_DEVICE_HPP

#include "QueueFamilyIndices.hpp"
#include "SwapChainSupportDetails.hpp"
#include "Instance.hpp"
#include "graphics/Window.hpp"
#include "utils/Logger.hpp"

#include <vulkan/vulkan.h>
#include <vector>
#include <memory>

namespace fs::graphics
{
class Device
{
public:

    void create(const Instance& instance, const Window& window);
    virtual void destroy();

    const VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling,
                                       VkFormatFeatureFlags features) const;

    const core::fs_uint32 findMemoryType(core::fs_uint32 typeFilter, VkMemoryPropertyFlags properties) const;

    SwapChainSupportDetails querySwapChainSupport() const;

    const QueueFamilyIndices& getQueueFamilyIndices() const;
    const SwapChainSupportDetails& getSwapChainSupportDetails() const;

    const Instance* getInstance() const;
    const Window* getWindow() const;

    const VkSurfaceKHR getSurface() const;
    const VkPhysicalDevice getPhysicalDevice() const;
    const VkDevice getDevice() const;
    const VkQueue getGraphicsQueue() const;
    const VkQueue getPresentationQueue() const;
    const VkCommandPool getCommandPool() const;

private:
    utils::LoggerPtr logger;

    const std::vector<const char*> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

    const Instance* instance = nullptr;
    const Window* window = nullptr;

    VkSurfaceKHR surface = VK_NULL_HANDLE;

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

    VkDevice device = VK_NULL_HANDLE;
    VkQueue graphicsQueue = VK_NULL_HANDLE;
    VkQueue presentationQueue = VK_NULL_HANDLE;
    VkCommandPool commandPool = VK_NULL_HANDLE;

    QueueFamilyIndices queueFamilyIndices;
    SwapChainSupportDetails swapChainSupportDetails;

private:
    void createSurface();

    void pickPhysicalDevice();
    bool pickDeviceIfSuitable(VkPhysicalDevice device);
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice physicalDevice) const;
    bool checkDeviceExtensionSupport(VkPhysicalDevice physicalDevice) const;
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice physicalDevice) const;

    void createLogicalDevice();
    void createCommandPool();
};

typedef std::unique_ptr<Device> DevicePtr;

}

#endif //FIRESTORM_DEVICE_HPP
