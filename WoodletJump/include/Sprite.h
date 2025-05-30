#pragma once

#include <Util/BufferBuilder.h>
#include <Util/TextureRect.h>
#include <Renderer/SpriteRenderer.h>

class Sprite {
public:
    void init(TextureRect texture_rect);
    void setSize(Vector2f size);
    void setPosition(Vector2f position);
    void setRotation(float rotation);
private:
    TextureBufferBuilder buffer_builder_;
    Vector2f position_{};
    Vector2f size_{};
    float rotation_{};

    friend void Renderer::SpriteRenderer::render(Sprite& sprite);
};
