


#ifndef FIRESTORM_RENDERPASS_HPP
#define FIRESTORM_RENDERPASS_HPP

#include "SwapChain.hpp"

#include <memory>

namespace fs::graphics
{
class RenderPass
{
public:
    RenderPass() = default;
    virtual ~RenderPass() = default;

    void create(const SwapChain& swapChain);
    virtual void destroy();

    const VkRenderPass getRenderPass() const;

private:
    const SwapChain* swapChain;

    VkRenderPass renderPass;

private:
    VkFormat findDepthFormat();
    VkAttachmentDescription getColorAttachmentDescription() const;
    VkAttachmentDescription getDepthAttachmentDescription();
};

typedef std::unique_ptr<RenderPass> RenderPassPtr;
}

#endif //FIRESTORM_RENDERPASS_HPP
