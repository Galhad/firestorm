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

#ifndef FIRESTORM_DEVICE_HPP
#define FIRESTORM_DEVICE_HPP

#include "QueueFamilyIndices.hpp"
#include "SwapChainSupportDetails.hpp"
#include "Instance.hpp"
#include "graphics/Window.hpp"

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
