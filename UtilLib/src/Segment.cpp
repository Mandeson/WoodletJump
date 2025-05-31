#include <Util/Segment.h>

Segment::Segment(BoxDF box, const TextureRect &texture_rect) : box_(box), texture_rect_(texture_rect) { }

const BoxDF &Segment::getBox() const {
    return box_;
}

const TextureRect &Segment::getTextureRect() const {
    return texture_rect_;
}
