


#ifndef FIRESTORM_INSTANCE_HPP
#define FIRESTORM_INSTANCE_HPP

#include "core/Types.hpp"
#include "utils/Logger.hpp"

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
    utils::LoggerPtr logger = spdlog::get(utils::CONSOLE_LOGGER_NAME);

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
