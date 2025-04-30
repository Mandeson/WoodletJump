#include <Sprite.h>

void Sprite::init(TextureRect texture_rect) {
    buffer_builder_.addRectangle({-0.5f, -0.5f}, {1.0f, 1.0f}, texture_rect);
    buffer_builder_.upload();
}

void Sprite::setSize(Vector2f size) {
    size_ = size;
}

void Sprite::setPosition(Vector2f position) {
    position_ = position;
}
