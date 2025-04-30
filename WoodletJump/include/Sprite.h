#pragma once

#include <Util/BufferBuilder.h>
#include <Util/TextureRect.h>
#include <Renderer/SpriteRenderer.h>

class Sprite {
public:
    void init(TextureRect texture_rect);
    void setSize(Vector2f size);
    void setPosition(Vector2f position);
private:
    BufferBuilder buffer_builder_;
    Vector2f position_{};
    Vector2f size_{};
    float rotation_{};

    friend void Renderer::SpriteRenderer::render(Sprite& sprite, const sf::Texture& texture);
};
