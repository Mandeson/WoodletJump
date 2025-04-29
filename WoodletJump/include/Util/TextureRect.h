#pragma once

#include <Util/Vector.h>

struct TextureRect {
    float s1, s2;
    float t1, t2;
    TextureRect(int texture_size, Vector2i pos, Vector2i size);
};
