#include <Player.h>
#include <SFML/Window/Keyboard.hpp>

Player::Player() : position_{0.2f, 0.6f - kPlayerSize / 2}, velocity_({0.0, 0.0}), acceleration_({0.0, 10.0}),
        is_jumping_(false) { }

void Player::init() {
    body_.init(kPlayerBodyTextureRect);
}

void Player::render(Renderer::SpriteRenderer &sprite_renderer, Vector2i window_size, const Camera &camera) {
    body_.setPosition({static_cast<float>(position_.x - camera.getPosition()) * window_size.y, static_cast<float>(position_.y) * window_size.y});
    float pixel_size = kPlayerSize * window_size.y;
    body_.setSize({pixel_size, pixel_size});
    sprite_renderer.render(body_);
}

void Player::getColisionBox(Box &box) {
    box = {{static_cast<float>(position_.x) - kPlayerHeadSize / 2, static_cast<float>(position_.y) - kPlayerHeadSize / 2},
            {kPlayerSize - 2 * kPlayerMargin, kPlayerSize - kPlayerMargin}};
}

void Player::timeStep(double d_time, const World::World &world, Camera &camera) {
    bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
    bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
    bool jump = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z);
    bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);

    if (!is_jumping_ && jump) {
        is_jumping_ = true;
        velocity_.y = kJumpVelocity;
    }

    velocity_.y += acceleration_.y * d_time;
    double move_time = d_time * kAccelerationMultiplier;
    Vector2d move = {velocity_.x * move_time, velocity_.y * move_time};
    if (right && !left) {
        move.x = d_time * kMoveMultiplier;
    } else if (left && !right) {
        move.x = -d_time * kMoveMultiplier;
    }
    if (up) {
        move.y = -d_time * kMoveMultiplier;
        velocity_.y = 0.0;
    }

    position_.x += move.x;
    position_.y += move.y;
    Box colision_box;
    getColisionBox(colision_box);
    if (world.checkCollision(camera, colision_box)) {
        position_.y -= move.y;
        Vector2d normalized = move.normalize();
        Vector2d move_less = {normalized.x * kCollisionThreshold, normalized.y * kCollisionThreshold};
        while (world.checkCollision(camera, colision_box)) {
            position_.x -= move_less.x;
            getColisionBox(colision_box);
        }

        position_.y += move.y;
        getColisionBox(colision_box);
        if (world.checkCollisionBelow(camera, colision_box)) {
            // Hit bottom, reset velocity etc.
            velocity_.y = 0.0;
            is_jumping_ = false;
        } else if (world.checkCollisionAbove(camera, colision_box)) { // hit a ceiling
            velocity_.y = 0.0;
        }
        while (world.checkCollision(camera, colision_box)) {
            position_.y -= move_less.y;
            getColisionBox(colision_box);
        }
    }

    camera.setPosition(position_.x - 0.2f);
}
