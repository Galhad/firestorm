


#include "DepthImage.hpp"

namespace fs::graphics
{

void DepthImage::create(const SwapChain& swapChain)
{
    this->swapChain = &swapChain;

    VkFormat depthFormat = findDepthFormat();
    Image::create(*swapChain.getDevice(), swapChain.getSwapChainExtent().width, swapChain.getSwapChainExtent().height,
                  depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
                  VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, VK_IMAGE_ASPECT_DEPTH_BIT);
    transitionImageLayout(image, depthFormat, VK_IMAGE_LAYOUT_UNDEFINED,
                          VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
}

void DepthImage::destroy()
{
    Image::destroy();
    swapChain = nullptr;
}

VkFormat DepthImage::findDepthFormat()
{
    return swapChain->getDevice()->findSupportedFormat(
        {VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
        VK_IMAGE_TILING_OPTIMAL,
        VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
    );
}

}
