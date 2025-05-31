#pragma once

#include <UI/UI.h>
#include <Util/Vector.h>

class WoodletJump;

namespace UI {

class Controls : public UI {
public:
    Controls(WoodletJump &game, float ui_scale);
    void init(sf::Font &font);
    void build(Vector2i window_size);
private:
    static constexpr Vector2i kControlsInfoViewDefaultSize = {180, 125};
    static constexpr const char *kControlsInfoText = "Controls:\n\n"
            "Z - jump\n"
            "Left arrow - move left\n"
            "Right arrow - move right\n"
            "X - ghost mode";

    WoodletJump &game_;
    ButtonID controls_info_view_;
    ButtonID back_button_;
};

}
