#include <UI/Credits.h>
#include <WoodletJump.h>

namespace UI {

Credits::Credits(WoodletJump &game, float ui_scale) : UI(ui_scale), game_(game) { }

void Credits::init(sf::Font &font) {
    UI::init(font);
    credits_view_ = addButton(kCreditsText, nullptr);
    back_button_ = addButton("Back", [&](){
        game_.active_ui_ = &game_.ui_pause_;
    });
}

void Credits::build(Vector2i window_size) {
    float scale = getUIScale();
    int width = static_cast<int>(Constants::kButtonDefaultSize.x * scale);
    int height = static_cast<int>(Constants::kButtonDefaultSize.y * scale);
    int margin = static_cast<int>(Constants::kMenuMarginDefault * scale);
    Vector2i view_size = {static_cast<int>(kCreditsViewDefaultSize.x * scale), 
        static_cast<int>(kCreditsViewDefaultSize.y * scale)};
    int pos_y = window_size.y / 2 - (view_size.y + margin + height) / 2;
    getButton(credits_view_).setBounds({{window_size.x / 2  - view_size.x / 2, pos_y}, view_size});
    pos_y += view_size.y + margin;
    getButton(back_button_).setBounds({{window_size.x / 2  - width / 2, pos_y}, {width, height}});
    UI::build();
}

}
