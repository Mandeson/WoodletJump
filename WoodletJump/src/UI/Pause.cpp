#include <UI/Pause.h>
#include <WoodletJump.h>

namespace UI {

Pause::Pause(WoodletJump &game, float ui_scale) : UI(ui_scale), game_(game) { }

void Pause::init(sf::Font &font) {
    UI::init(font);
    button_ = addButton("Button");
}

void Pause::build(Vector2i window_size) {
    if (!button_)
        throw UI::NotInitialised();
    float scale = getUIScale();
    int width = static_cast<int>(kButtonDefaultSize.x * scale);
    int height = static_cast<int>(kButtonDefaultSize.y * scale);
    button_->setBounds({{window_size.x / 2  - width / 2, window_size.y / 2 - height / 2}, {width, height}});
    UI::build();
}

}
