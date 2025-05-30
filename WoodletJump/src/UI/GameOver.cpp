#include <UI/GameOver.h>
#include <WoodletJump.h>
#include <Constants.h>

namespace UI {

GameOver::GameOver(WoodletJump &game, float ui_scale) : UI(ui_scale), game_(game) { }

void GameOver::init(sf::Font &font) {
    UI::init(font);
    retry_button_ = addButton("Retry", [&](){
        game_.player_.reset();
        game_.camera_.reset();
        game_.world_.reset();
        game_.active_ui_ = nullptr;
    });

    sf::Text &text = text_.emplace(font, "Game Over!");
    text.setCharacterSize(static_cast<unsigned int>(getUIScale() * kTextDefaultFontSize));
    float origin = text.getGlobalBounds().size.x / 2 + text.getLocalBounds().position.x;
    text.setOrigin({std::round(origin), 0.0f});
    text.setFillColor(sf::Color{180, 50, 50});
}

void GameOver::build(Vector2i window_size) {
    float scale = getUIScale();
    int width = static_cast<int>(Constants::kButtonDefaultSize.x * scale);
    int height = static_cast<int>(Constants::kButtonDefaultSize.y * scale);
    int pos_y = window_size.y / 2 - (kTextDefaultFontSize * 2 + height) / 2;
    const int pos_x = window_size.x / 2  - width / 2;
    text_.value().setPosition({static_cast<float>(window_size.x / 2), static_cast<float>(pos_y)});   
    pos_y += kTextDefaultFontSize * 2;
    getButton(retry_button_).setBounds({{pos_x, pos_y}, {width, height}});
    UI::build();
}

void GameOver::renderGameOver(sf::RenderWindow &window) {
    if (!text_)
        throw UI::NotInitialised();
    window.draw(text_.value());
}

}
