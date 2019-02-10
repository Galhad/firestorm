


#ifndef FIRESTORM_DEPTHIMAGE_HPP
#define FIRESTORM_DEPTHIMAGE_HPP

#include "Image.hpp"
#include "SwapChain.hpp"

#include <memory>

namespace fs::graphics
{
class DepthImage : public Image
{
public:
    DepthImage() = default;
    ~DepthImage() override = default;

    void create(const SwapChain& swapChain);
    void destroy() override;

private:
    const SwapChain* swapChain = nullptr;
    VkFormat findDepthFormat();
};

typedef std::unique_ptr<DepthImage> DepthImagePtr;
}

#endif //FIRESTORM_DEPTHIMAGE_HPP
