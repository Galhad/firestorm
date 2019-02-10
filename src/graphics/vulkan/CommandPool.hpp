


#ifndef FIRESTORM_COMMANDPOOL_HPP
#define FIRESTORM_COMMANDPOOL_HPP

#include "core/Types.hpp"

#include <vulkan/vulkan.h>

#include <memory>

namespace fs::graphics
{
class CommandPool
{
public:
    CommandPool() = default;
    virtual ~CommandPool() = default;

    void create(VkDevice device, core::fs_uint32 queueFamilyIndex);
    void destroy();

    const VkCommandPool getCommandPool() const;

private:
    VkDevice device = VK_NULL_HANDLE;

    VkCommandPool commandPool = VK_NULL_HANDLE;
};

typedef std::unique_ptr<CommandPool> CommandPoolPtr;

}
#endif //FIRESTORM_COMMANDPOOL_HPP
