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

#include "Instance.hpp"

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

#include <vector>
#include <sstream>
#include <cstring>

namespace fs::graphics
{

VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo,
                                      const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback)
{
    auto func = (PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
    if (func != nullptr)
    {
        return func(instance, pCreateInfo, pAllocator, pCallback);
    }
    else
    {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback,
                                   const VkAllocationCallbacks* pAllocator)
{
    auto func = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(instance,
                                                                            "vkDestroyDebugReportCallbackEXT");
    if (func != nullptr)
    {
        func(instance, callback, pAllocator);
    }
}

void
Instance::create(const std::string& applicationName, core::fs_uint8 applicationVersionMajor,
                 core::fs_uint8 applicationVersionMinor, core::fs_uint8 applicationVersionPath,
                 bool enableValidationLayers)
{
    logger = spdlog::get(utils::CONSOLE_LOGGER_NAME);

    this->validationLayersEnabled = enableValidationLayers;
    if (enableValidationLayers)
    {
        logger->info("Validation layers are enabled.");

        if (!checkValidationLayerSupport())
        {
            throw std::runtime_error("Validation layers requested, but not available!");
        }
    }

    auto appInfo = getApplicationInfo(applicationName, VK_MAKE_VERSION(applicationVersionMajor, applicationVersionMinor,
                                                                       applicationVersionPath));

    const auto& requiredExtensions = getRequiredExtensions();

    uint32_t extensionsCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, nullptr);

    std::vector<VkExtensionProperties> extensions(extensionsCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, extensions.data());

    printAvailableExtensions(extensions);
    validateRequiredExtensions(extensions, requiredExtensions);

    auto createInfo = getInstanceCreateInfo(appInfo, requiredExtensions);

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create Vulkan instance!");
    }

    setupDebugCallback();
}

void Instance::destroy()
{
    DestroyDebugReportCallbackEXT(instance, callback, nullptr);
    callback = VK_NULL_HANDLE;

    vkDestroyInstance(instance, nullptr);
    instance = VK_NULL_HANDLE;
}

bool Instance::checkValidationLayerSupport() const
{
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const auto& layerName : validationLayers)
    {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers)
        {
            if (strcmp(layerName, layerProperties.layerName) == 0)
            {
                layerFound = true;
                break;
            }
        }

        if (!layerFound)
        {
            return false;
        }
    }

    return true;
}

VkApplicationInfo
Instance::getApplicationInfo(const std::string& applicationName, core::fs_uint32 applicationVersion) const
{
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = applicationName.c_str();
    appInfo.applicationVersion = applicationVersion;
    appInfo.pEngineName = "Firestorm";
    appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0); // todo: Set engine version
    appInfo.apiVersion = VK_API_VERSION_1_0;
    return appInfo;
}

std::vector<const char*> Instance::getRequiredExtensions() const
{
    std::vector<const char*> extensions;

    uint32_t glfwExtensionsCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionsCount);

    for (unsigned int i = 0; i < glfwExtensionsCount; ++i)
    {
        extensions.push_back(glfwExtensions[i]);
    }

    if (validationLayersEnabled)
    {
        extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
    }

    return extensions;
}

void Instance::printAvailableExtensions(const std::vector<VkExtensionProperties>& extensions)
{
    logger->debug("Available Vulkan extensions:");
    for (const auto& extension : extensions)
    {
        logger->debug("\t {}", extension.extensionName);
    }
}

void Instance::validateRequiredExtensions(const std::vector<VkExtensionProperties>& availableExtensions,
                                          const std::vector<const char*>& requiredExtensions) const
{
    for (const auto& requiredExtension : requiredExtensions)
    {
        bool found = false;
        for (const auto& availableExtension : availableExtensions)
        {
            if (strcmp(availableExtension.extensionName, requiredExtension) == 0)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            std::stringstream message;
            message << "Extension " << requiredExtension << " is not available!";
            throw std::runtime_error(message.str());
        }
    }
}

VkInstanceCreateInfo
Instance::getInstanceCreateInfo(const VkApplicationInfo& appInfo,
                                const std::vector<const char*>& extensions) const
{
    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();
    if (validationLayersEnabled)
    {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    }
    else
    {
        createInfo.enabledLayerCount = 0;
    }
    return createInfo;
}

void Instance::setupDebugCallback()
{
    if (!validationLayersEnabled) return;

    VkDebugReportCallbackCreateInfoEXT createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
    createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
    createInfo.pfnCallback = debugCallback;
    createInfo.pUserData = logger.get();

    if (CreateDebugReportCallbackEXT(instance, &createInfo, nullptr, &callback) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to set up debug callback.");
    }
}

VkBool32 Instance::debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType,
                                 uint64_t object, size_t location, int32_t code,
                                 const char* layerPrefix, const char* message, void* userData)
{
    if (userData != nullptr)
    {
        static_cast<utils::Logger*>(userData)->error("Validation layer: {}", message);
    }

    return VK_FALSE;
}

VkInstance Instance::getInstance() const
{
    return instance;
}

bool Instance::areValidationLayersEnabled() const
{
    return validationLayersEnabled;
}

const std::vector<const char*>& Instance::getValidationLayers() const
{
    return validationLayers;
}

}
