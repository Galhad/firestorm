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

#include "TextureImage.hpp"
#include "CommandBuffer.hpp"

#include <cstring>

namespace fs::graphics
{

void
TextureImage::create(const Device& device, core::fs_uint32 width, core::fs_uint32 height, const core::fs_uint8* bytes,
                     core::fs_uint64 size)
{
    this->device = &device;

    buffer.create(device, size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                  VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

    void* data;
    vkMapMemory(static_cast<VkDevice>(device), static_cast<VkDeviceMemory>(buffer), 0, size, 0, &data);
    memcpy(data, bytes, static_cast<size_t>(size));
    vkUnmapMemory(static_cast<VkDevice>(device), static_cast<VkDeviceMemory>(buffer));

    VkFormat format = VK_FORMAT_R8G8B8A8_UNORM;
    createImage(width, height, format, VK_IMAGE_TILING_OPTIMAL,
                VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

    transitionImageLayout(image, format, VK_IMAGE_LAYOUT_UNDEFINED,
                          VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    copyBufferToImage(width, height);

    transitionImageLayout(image, format, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                          VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    createImageView(format, VK_IMAGE_ASPECT_COLOR_BIT);
    // TODO
    // For practical applications it is recommended to combine these operations in a single command buffer and
    // execute them asynchronously for higher throughput, especially the transitions and copy in the createTextureImage function.
    // Try to experiment with this by creating a setupCommandBuffer that the helper functions record commands into,
    // and add a flushSetupCommands to execute the commands that have been recorded so far.
}

void TextureImage::destroy()
{
    buffer.destroy();
    Image::destroy();
}

void TextureImage::copyBufferToImage(core::fs_uint32 width, core::fs_uint32 height)
{
    CommandBuffer commandBuffer;
    commandBuffer.create(*device);
    commandBuffer.beginSingleTimeCommand();

    VkBufferImageCopy region = {};
    region.bufferOffset = 0;
    region.bufferRowLength = 0;
    region.bufferImageHeight = 0;

    region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    region.imageSubresource.mipLevel = 0;
    region.imageSubresource.baseArrayLayer = 0;
    region.imageSubresource.layerCount = 1;

    region.imageOffset = {0, 0, 0};
    region.imageExtent = {
        width,
        height,
        1
    };

    vkCmdCopyBufferToImage(
        commandBuffer.getCommandBuffer(),
        static_cast<VkBuffer>(buffer),
        image,
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
        1,
        &region
    );

    commandBuffer.endSingleTimeCommand();
    commandBuffer.destroy();
}
}

