#include <Player.h>
#include <SFML/Window/Keyboard.hpp>

Player::Player() : position_{0.2f, 0.6f - 0.07f / 2} { }

void Player::init() {
    body_.init(kPlayerBodyTextureRect);
}

void Player::render(Renderer::SpriteRenderer &sprite_renderer, Vector2i window_size) {
    body_.setPosition({static_cast<float>(position_.x * window_size.y), static_cast<float>(position_.y * window_size.y)});
    float pixel_size = 0.07f * window_size.y;
    body_.setSize({pixel_size, pixel_size});
    sprite_renderer.render(body_);
}

void Player::timeStep(double d_time) {
    double move = d_time / 10;
    bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
    bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
    bool jump = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z);

    if (right && !left) {
        position_.x += move;
    } else if (left && !right) {
        position_.x -= move;
    }
}
