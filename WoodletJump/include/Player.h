#pragma once

#include <Sprite.h>
#include <Util/Vector.h>
#include <Constants.h>

class Player {
public:
    Player();
    void init();
    void render(Renderer::SpriteRenderer &sprite_renderer, Vector2i window_size);
private:
    static constexpr TextureRect kPlayerBodyTextureRect = TextureRect(Constants::kTextureSize, {0, 0}, {82, 82});
    Sprite body_;
    Vector2f position_;
};
