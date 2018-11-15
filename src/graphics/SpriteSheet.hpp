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
    virtual ~SpriteSheet() = default;

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
    const fs::graphics::GraphicsPipeline* graphicsPipeline = nullptr;

    std::list<Sprite> sprites;
    bool spritesChanged = true;

};

typedef std::unique_ptr<SpriteSheet> SpriteSheetPtr;
}

#endif //FIRESTORM_SPRITESHEET_HPP
