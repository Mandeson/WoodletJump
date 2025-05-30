#pragma once

#include <UI/UI.h>
#include <Util/Vector.h>
#include <optional>

class WoodletJump;

namespace UI {

class GameOver : public UI {
public:
    GameOver(WoodletJump &game, float ui_scale);
    void init(sf::Font &font);
    void build(Vector2i window_size);
    void renderGameOver(sf::RenderWindow &window);
private:
    static constexpr int kTextDefaultFontSize = 40;

    WoodletJump &game_;
    ButtonID retry_button_;
    std::optional<sf::Text> text_{};
};

}
