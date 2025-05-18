#pragma once

#include <Util/Box.h>
#include <Util/TextureRect.h>

class Segment {
public:
    Segment(Box box, const TextureRect &texture_rect);
    const Box &getBox() const;
    const TextureRect &getTextureRect() const;
private:
    const Box box_;
    const TextureRect &texture_rect_;
};
