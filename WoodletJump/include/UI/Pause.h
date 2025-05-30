#pragma once

#include <UI/UI.h>
#include <Util/Vector.h>

class WoodletJump;

namespace UI {

class Pause : public UI {
public:
    Pause(WoodletJump &game, float ui_scale);
    void init(sf::Font &font);
    void build(Vector2i window_size);
private:
    WoodletJump &game_;
    ButtonID back_button_;
    ButtonID settings_button_;
};

}
