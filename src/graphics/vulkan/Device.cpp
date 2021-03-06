


#include "Device.hpp"

#include <set>

namespace fs::graphics
{
void Device::create(const Instance& instance, const Window& window)
{
    logger = spdlog::get(utils::CONSOLE_LOGGER_NAME);

    this->instance = &instance;
    this->window = &window;

    createSurface();
    pickPhysicalDevice();
    createLogicalDevice();
    createCommandPool();
}

void Device::destroy()
{
    vkDestroyCommandPool(device, commandPool, nullptr);

    vkDestroyDevice(device, nullptr);

    window = nullptr;
    instance = VK_NULL_HANDLE;
}

void Device::createSurface()
{
    if (glfwCreateWindowSurface(instance->getInstance(), window->getWindow(), nullptr, &surface) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create window surface.");
    }
}

void Device::pickPhysicalDevice()
{
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance->getInstance(), &deviceCount, nullptr);
    if (deviceCount == 0)
    {
        throw std::runtime_error("Failed to find GPUs with Vulkan support.");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance->getInstance(), &deviceCount, devices.data());

    for (const auto& device : devices)
    {
        if (pickDeviceIfSuitable(device))
        {
            break;
        }
    }

    if (physicalDevice == VK_NULL_HANDLE)
    {
        throw std::runtime_error("Failed to find a suitable GPU!");
    }
}

bool Device::pickDeviceIfSuitable(VkPhysicalDevice device)
{
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);

    VkPhysicalDeviceFeatures deviceFeatures = {};
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    logger->debug("Found device {} ({}) with driver version {} vendor id {}", deviceProperties.deviceName,
                  deviceProperties.deviceID,
                  deviceProperties.driverVersion, deviceProperties.vendorID);
    logger->debug("Maximum texture size: {}", deviceProperties.limits.maxImageDimension2D);

    QueueFamilyIndices indices = findQueueFamilies(device);
    bool extensionsSupported = checkDeviceExtensionSupport(device);

    SwapChainSupportDetails swapChainSupportDetails = querySwapChainSupport(device);

    bool swapChainAdequate =
        extensionsSupported && !swapChainSupportDetails.formats.empty() &&
        !swapChainSupportDetails.presentModes.empty();

    if (/*deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && */deviceFeatures.geometryShader &&
                                                                                   indices.isComplete() &&
                                                                                   extensionsSupported &&
                                                                                   swapChainAdequate &&
                                                                                   deviceFeatures.samplerAnisotropy)
    {
        logger->info("Device {} is suitable", deviceProperties.deviceName);

        physicalDevice = device;
        this->swapChainSupportDetails = swapChainSupportDetails;
        this->queueFamilyIndices = indices;

        return true;
    }
    else
    {
        return false;
    }
}

QueueFamilyIndices Device::findQueueFamilies(VkPhysicalDevice physicalDevice) const
{
    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto& queueFamily : queueFamilies)
    {
        if (queueFamily.queueCount > 0)
        {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                indices.graphicsFamily = i;
            }

            VkBool32 presentationSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &presentationSupport);
            if (presentationSupport)
            {
                indices.presentFamily = i;
            }
        }
        // todo: prefer device which has both families in the same queue

        if (indices.isComplete())
        {
            break;
        }

        ++i;
    }

    return indices;
}

bool Device::checkDeviceExtensionSupport(VkPhysicalDevice physicalDevice) const
{
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, availableExtensions.data());

    std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

    for (const auto& extension : availableExtensions)
    {
        requiredExtensions.erase(extension.extensionName);
    }

    return requiredExtensions.empty();
}

SwapChainSupportDetails Device::querySwapChainSupport(VkPhysicalDevice physicalDevice) const
{
    SwapChainSupportDetails details;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &details.capabilities);

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, nullptr);

    if (formatCount != 0)
    {
        details.formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, details.formats.data());
    }

    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, nullptr);

    if (presentModeCount != 0)
    {
        details.presentModes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount,
                                                  details.presentModes.data());
    }

    return details;
}

void Device::createLogicalDevice()
{
    QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<int> uniqueQueueFamilies = {indices.graphicsFamily, indices.presentFamily};

    float queuePriority[] = {1.0f};
    for (int queueFamily : uniqueQueueFamilies)
    {
        VkDeviceQueueCreateInfo queueCreateInfo = {};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = static_cast<uint32_t>(queueFamily);
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkPhysicalDeviceFeatures deviceFeatures = {};
    deviceFeatures.samplerAnisotropy = VK_TRUE;

    VkDeviceCreateInfo deviceCreateInfo = {};
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
    deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    deviceCreateInfo.pEnabledFeatures = &deviceFeatures;
    deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
    deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data();

    if (instance->areValidationLayersEnabled())
    {
        const auto& validationLayers = instance->getValidationLayers();
        deviceCreateInfo.enabledLayerCount = static_cast<uint32_t> (validationLayers.size());
        deviceCreateInfo.ppEnabledLayerNames = validationLayers.data();
    }
    else
    {
        deviceCreateInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &device) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create logical device.");
    }

    vkGetDeviceQueue(device, static_cast<uint32_t>(indices.graphicsFamily), 0, &graphicsQueue);
    vkGetDeviceQueue(device, static_cast<uint32_t>(indices.presentFamily), 0, &presentationQueue);
}

const QueueFamilyIndices& Device::getQueueFamilyIndices() const
{
    return queueFamilyIndices;
}

const SwapChainSupportDetails& Device::getSwapChainSupportDetails() const
{
    return swapChainSupportDetails;
}

const Instance* Device::getInstance() const
{
    return instance;
}

const Window* Device::getWindow() const
{
    return window;
}

const VkSurfaceKHR Device::getSurface() const
{
    return surface;
}

const VkPhysicalDevice Device::getPhysicalDevice() const
{
    return physicalDevice;
}

const VkDevice Device::getDevice() const
{
    return device;
}

const VkQueue Device::getGraphicsQueue() const
{
    return graphicsQueue;
}

const VkQueue Device::getPresentationQueue() const
{
    return presentationQueue;
}

const VkFormat Device::findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling,
                                           VkFormatFeatureFlags features) const
{
    for (VkFormat format : candidates)
    {
        VkFormatProperties props;
        vkGetPhysicalDeviceFormatProperties(physicalDevice, format, &props);

        if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features)
        {
            return format;
        }
        else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features)
        {
            return format;
        }
    }

    throw std::runtime_error("Failed to find supported format!");
}

const VkCommandPool Device::getCommandPool() const
{
    return commandPool;
}

void Device::createCommandPool()
{
    VkCommandPoolCreateInfo commandPoolCreateInfo = {};
    commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    commandPoolCreateInfo.queueFamilyIndex = static_cast<uint32_t>(queueFamilyIndices.graphicsFamily);
    commandPoolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

    if (vkCreateCommandPool(device, &commandPoolCreateInfo, nullptr, &commandPool) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create command pool.");
    }
}

const core::fs_uint32 Device::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) const
{
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
    {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
        {
            return i;
        }
    }

    throw std::runtime_error("Failed to find suitable memory type.");
}

SwapChainSupportDetails Device::querySwapChainSupport() const
{
    return querySwapChainSupport(physicalDevice);
}


}
