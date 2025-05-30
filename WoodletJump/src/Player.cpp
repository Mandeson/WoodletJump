#include <Player.h>
#include <SFML/Window/Keyboard.hpp>

Player::Player() {
    reset();
}

void Player::init() {
    body_.init(kPlayerBodyTextureRect);
}

void Player::reset() {
    position_ = {0.0f, 0.6f - kPlayerSize / 2 - kCollisionThreshold};
    velocity_ = {0.0, 0.0};
    acceleration_ = {0.0, 10.0};
    tilt_ = 0.0f;
    is_jumping_ = false;
    is_coliding_ = true;
}

void Player::render(Renderer::SpriteRenderer &sprite_renderer, Vector2i window_size, const Camera &camera) {
    body_.setPosition({static_cast<float>(position_.x - camera.getPosition()) * window_size.y, static_cast<float>(position_.y) * window_size.y});
    float pixel_size = kPlayerSize * window_size.y;
    body_.setSize({pixel_size, pixel_size});
    body_.setRotation(tilt_);
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
    bool collide = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X);
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
        tilt_ = std::min(tilt_ + static_cast<float>(d_time) * kTiltAngularSpeed, 1.0f);
    } else if (left && !right) {
        move.x = -d_time * kMoveMultiplier;
        tilt_ = std::max(tilt_ - static_cast<float>(d_time) * kTiltAngularSpeed, -1.0f);
    } else {
        if (tilt_ > 0)
            tilt_ = std::max(tilt_ - static_cast<float>(d_time) * kTiltAngularSpeed, 0.0f);
        else
            tilt_ = std::min(tilt_ + static_cast<float>(d_time) * kTiltAngularSpeed, 0.0f);
    }
    if (up) {
        move.y = -d_time * kMoveMultiplier;
        velocity_.y = 0.0;
    }

    position_.x += move.x;
    position_.y += move.y;
    Box colision_box;
    if (is_coliding_) {
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
                if (collide)
                    is_coliding_ = false;
                velocity_.y = 0.0;
                is_jumping_ = false;
            } else if (world.checkCollisionAbove(camera, colision_box)) { // hit a ceiling
                velocity_.y = 0.0;
            }
            while (world.checkCollision(camera, colision_box)) {
                position_.y -= move_less.y;
                getColisionBox(colision_box);
            }
        } else if (collide) {
            is_coliding_ = false;
        }
    } else if (!collide) {
        getColisionBox(colision_box);
        if (!world.checkCollision(camera, colision_box)) {
            is_coliding_ = true;
        }
    }

    camera.setPosition(position_.x - 0.2f);
}

bool Player::gameOver() {
    return position_.y > 1.0f;
}

double Player::getWorldPosition() {
    return position_.x;
}
