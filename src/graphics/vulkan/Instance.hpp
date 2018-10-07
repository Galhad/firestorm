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

#ifndef FIRESTORM_INSTANCE_HPP
#define FIRESTORM_INSTANCE_HPP

#include "core/Types.hpp"

#include <vulkan/vulkan.h>
#include <memory>
#include <vector>

namespace fs::graphics
{
class Instance
{
public:
    Instance() = default;
    ~Instance() = default;

    void create(const std::string& applicationName, core::fs_uint8 applicationVersionMajor,
                core::fs_uint8 applicationVersionMinor, core::fs_uint8 applicationVersionPath,
                bool enableValidationLayers);
    virtual void destroy();

    VkInstance getInstance() const;

    bool areValidationLayersEnabled() const;
    const std::vector<const char*>& getValidationLayers() const;


private:
    bool validationLayersEnabled = false;

    const std::vector<const char*> validationLayers = {"VK_LAYER_LUNARG_standard_validation"};

    VkInstance instance = VK_NULL_HANDLE;
    VkDebugReportCallbackEXT callback = VK_NULL_HANDLE;

private:
    bool checkValidationLayerSupport() const;
    VkApplicationInfo getApplicationInfo(const std::string& applicationName, core::fs_uint32 applicationVersion) const;
    std::vector<const char*> getRequiredExtensions() const;
    void printAvailableExtensions(const std::vector<VkExtensionProperties>& extensions);
    void validateRequiredExtensions(const std::vector<VkExtensionProperties>& availableExtensions,
                                    const std::vector<const char*>& requiredExtensions) const;
    VkInstanceCreateInfo
    getInstanceCreateInfo(const VkApplicationInfo& appInfo, const std::vector<const char*>& extensions) const;

    void setupDebugCallback();
    static VKAPI_ATTR VkBool32 debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType,
                                             uint64_t object, size_t location, int32_t code,
                                             const char* layerPrefix, const char* message, void* userData);

};

typedef std::unique_ptr<Instance> InstancePtr;

}

#endif //FIRESTORM_INSTANCE_HPP
