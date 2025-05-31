#pragma once

#include <Util/Vector.h>

struct Box {
    Vector2f position;
    Vector2f size;
};

struct BoxDF {
    Vector2d position;
    Vector2f size;
};

struct BoxI {
    Vector2i position;
    Vector2i size;
};
