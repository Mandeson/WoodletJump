#pragma once

#include <Sprite.h>
#include <Util/Vector.h>
#include <Constants.h>
#include <World/World.h>

class Player {
public:
    Player();
    void init();
    void render(Renderer::SpriteRenderer &sprite_renderer, Vector2i window_size);
    void timeStep(double d_time, const World::World &world, const Camera &camera);
private:
    static constexpr TextureRect kPlayerBodyTextureRect = TextureRect(Constants::kTextureSize, {0, 0}, {82, 82});
    static constexpr float kPlayerSize = 0.07f;
    static constexpr float kPlayerMargin = 0.015f;
    static constexpr float kPlayerHeadSize = (kPlayerSize - 2 * kPlayerMargin);
    static constexpr float kCollisionThreshold = 1.0f / 1440 / 32;

    void getColisionBox(Box &box);

    Sprite body_;
    Vector2d position_;
};
