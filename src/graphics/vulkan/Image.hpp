


#ifndef FIRESTORM_IMAGE_HPP
#define FIRESTORM_IMAGE_HPP

#include "Device.hpp"

#include <vulkan/vulkan.h>
#include <memory>

namespace fs::graphics
{
class Image
{
public:
    Image() = default;
    virtual ~Image() = 0;

    void create(const Device& device, uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling,
                VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImageAspectFlags aspectFlags);
    virtual void destroy();

    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);

    const VkImageView getImageView() const;

protected:
    const Device* device = nullptr;

    VkImage image = VK_NULL_HANDLE;
    VkDeviceMemory imageMemory = VK_NULL_HANDLE;
    VkImageView imageView = VK_NULL_HANDLE;

protected:
    void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage,
                     VkMemoryPropertyFlags properties);
    void createImageView(VkFormat format, VkImageAspectFlags aspectFlags);
    bool hasStencilComponent(VkFormat format);
};

typedef std::unique_ptr<Image> ImagePtr;

}
#endif //FIRESTORM_IMAGE_HPP
