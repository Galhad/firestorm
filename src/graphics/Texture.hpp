


#ifndef FIRESTORM_TEXTURE_HPP
#define FIRESTORM_TEXTURE_HPP

#include "core/Types.hpp"
#include "vulkan/TextureImage.hpp"

#include <memory>

namespace fs::graphics
{

class Texture
{
public:
    Texture() = default;
    virtual ~Texture() = default;

    void create(TextureImage textureImage, core::fs_uint32 width, core::fs_uint32 height,
                core::fs_uint32 pixelsPerUnit = 100, core::fs_uint32 channels = 4);
    virtual void destroy();

    core::fs_uint32 getWidthPixels() const;
    core::fs_float32 getWidthUnits() const;

    core::fs_uint32 getHeightPixels() const;
    core::fs_float32 getHeightUnits() const;

    core::fs_uint32 getChannels() const;

    const TextureImage& getTextureImage() const;

    core::fs_uint32 getPixelsPerUnit() const;

protected:
    core::fs_uint32 width = 0;
    core::fs_uint32 height = 0;
    core::fs_uint32 channels = 0;
    TextureImage textureImage;
    core::fs_uint32 pixelsPerUnit = 100;
};

typedef std::unique_ptr<Texture> TexturePtr;
}

#endif //FIRESTORM_TEXTURE_HPP
