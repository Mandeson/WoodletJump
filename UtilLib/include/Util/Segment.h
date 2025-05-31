#pragma once

#include <Util/Box.h>
#include <Util/TextureRect.h>

class Segment {
public:
    Segment(BoxDF box, const TextureRect &texture_rect);
    const BoxDF &getBox() const;
    const TextureRect &getTextureRect() const;
private:
    const BoxDF box_;
    const TextureRect &texture_rect_;
};
