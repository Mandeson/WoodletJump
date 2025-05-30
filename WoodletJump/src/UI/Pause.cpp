#include <UI/Pause.h>
#include <WoodletJump.h>
#include <Constants.h>

namespace UI {

Pause::Pause(WoodletJump &game, float ui_scale) : UI(ui_scale), game_(game) { }

void Pause::init(sf::Font &font) {
    UI::init(font);
    back_button_ = addButton("Back", [&](){
        game_.active_ui_ = nullptr;
    });
    settings_button_ = addButton("Controls", [&](){
        game_.active_ui_ = &game_.ui_controls_;
    });
    credits_button_ = addButton("Credits", [&](){
        game_.active_ui_ = &game_.ui_credits_;
    });
}

void Pause::build(Vector2i window_size) {
    float scale = getUIScale();
    int width = static_cast<int>(Constants::kButtonDefaultSize.x * scale);
    int height = static_cast<int>(Constants::kButtonDefaultSize.y * scale);
    int margin = static_cast<int>(Constants::kMenuMarginDefault * scale);
    int pos_y = window_size.y / 2 - (height * 3 + margin * (3 - 1)) / 2;
    const int pos_x = window_size.x / 2  - width / 2;
    getButton(back_button_).setBounds({{pos_x, pos_y}, {width, height}});
    pos_y += height + margin;
    getButton(settings_button_).setBounds({{pos_x, pos_y}, {width, height}});
    pos_y += height + margin;
    getButton(credits_button_).setBounds({{pos_x, pos_y}, {width, height}});
    UI::build();
}

}
