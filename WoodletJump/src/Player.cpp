#include <Player.h>

Player::Player() : position_{0.1f, 0.8f} { }

void Player::init() {
    body_.init(kPlayerBodyTextureRect);
}

void Player::render(Renderer::SpriteRenderer &sprite_renderer, Vector2i window_size) {
    body_.setPosition({position_.x * window_size.y, position_.y * window_size.y});
    float pixel_size = 0.07f * window_size.y;
    body_.setSize({pixel_size, pixel_size});
    sprite_renderer.render(body_);
}
