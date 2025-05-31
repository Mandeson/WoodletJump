#pragma once

#include <Util/BufferBuilder.h>
#include <Renderer/ColorRenderer.h>

class Background {
public:
    void render(Renderer::ColorRenderer &renderer, Vector2i window_size);
private:
    static constexpr Color kColorTop = Color{120, 220, 160};
    static constexpr Color kColorBottom = Color{60, 180, 80};

    ColorBufferBuilder buffer_builder_;
};
