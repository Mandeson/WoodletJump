#include <UI/Controls.h>
#include <WoodletJump.h>

namespace UI {

Controls::Controls(WoodletJump &game, float ui_scale) : UI(ui_scale), game_(game) { }

void Controls::init(sf::Font &font) {
    UI::init(font);
    controls_info_view_ = addButton(kControlsInfoText, nullptr);
    back_button_ = addButton("Back", [&](){
        game_.active_ui_ = &game_.ui_pause_;
    });
}

void Controls::build(Vector2i window_size) {
    float scale = getUIScale();
    int width = static_cast<int>(Constants::kButtonDefaultSize.x * scale);
    int height = static_cast<int>(Constants::kButtonDefaultSize.y * scale);
    int margin = static_cast<int>(Constants::kMenuMarginDefault * scale);
    Vector2i view_size = {static_cast<int>(kControlsInfoViewDefaultSize.x * scale), 
        static_cast<int>(kControlsInfoViewDefaultSize.y * scale)};
    int pos_y = window_size.y / 2 - (view_size.y + margin + height) / 2;
    getButton(controls_info_view_).setBounds({{window_size.x / 2  - view_size.x / 2, pos_y}, view_size});
    pos_y += view_size.y + margin;
    getButton(back_button_).setBounds({{window_size.x / 2  - width / 2, pos_y}, {width, height}});
    UI::build();
}

}
