#pragma once

#include <Util/Vector.h>

struct TextureRect {
    float s1, s2;
    float t1, t2;
    constexpr TextureRect(int texture_size, Vector2i pos, Vector2i size) {
        s1 = static_cast<float>(pos.x) / texture_size;
        s2 = static_cast<float>(pos.x + size.x) / texture_size;
        t1 = static_cast<float>(pos.y) / texture_size;
        t2 = static_cast<float>(pos.y + size.y) / texture_size;
    }
};
