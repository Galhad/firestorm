


#ifndef FIRESTORM_TEXTUREIMAGE_HPP
#define FIRESTORM_TEXTUREIMAGE_HPP

#include "Image.hpp"
#include "Buffer.hpp"

#include <memory>
#include <cstdint>

namespace fs::graphics
{
class TextureImage : public Image
{
public:
    TextureImage() = default;
    ~TextureImage() override = default;

    void create(const Device& device, core::fs_uint32 width, core::fs_uint32 height, const core::fs_uint8* bytes,
                core::fs_uint64 size);
    void destroy() override;

    const VkDescriptorImageInfo& getDescriptorImageInfo() const;

protected:
    VkDescriptorImageInfo descriptorImageInfo = {};
    VkSampler sampler = VK_NULL_HANDLE;
    VkImageLayout imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

protected:
    void copyBufferToImage(core::fs_uint32 width, core::fs_uint32 height, const Buffer& buffer);

    void createSampler();
};

typedef std::unique_ptr<TextureImage> TextureImagePtr;
}

#endif //FIRESTORM_TEXTUREIMAGE_HPP
