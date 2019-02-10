


#ifndef FIRESTORM_SPRITESHEET_HPP
#define FIRESTORM_SPRITESHEET_HPP

#include "Texture.hpp"
#include "Sprite.hpp"

#include <memory>
#include <list>

namespace fs::graphics
{
class SpriteSheet : public Texture
{
public:
    SpriteSheet() = default;
    ~SpriteSheet() override = default;

    void
    create(const fs::graphics::GraphicsPipeline& graphicsPipeline, TextureImage textureImage, core::fs_uint32 width,
           core::fs_uint32 height,
           core::fs_uint32 pixelsPerUnit = 100, core::fs_uint32 channels = 4);
    void destroy() override;

    Sprite* addSprite(core::Recti rect);
    bool removeSprite(Sprite* sprite);
    void clearSprites();

    const std::list<Sprite>& getSprites() const;
    std::list<Sprite>& getSprites();

    bool areSpritesChanged() const;
    void setSpritesChanged(bool spritesChanged);

private:
    void createDescriptor();
    void destroyDescriptor();

private:
    const fs::graphics::GraphicsPipeline* graphicsPipeline = nullptr;

    std::list<Sprite> sprites;
    bool spritesChanged = true;

    VkDescriptorSet descriptorSet = VK_NULL_HANDLE;

};

typedef std::unique_ptr<SpriteSheet> SpriteSheetPtr;
}

#endif //FIRESTORM_SPRITESHEET_HPP
