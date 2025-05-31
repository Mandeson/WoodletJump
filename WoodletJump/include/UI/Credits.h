#pragma once

#include <UI/UI.h>
#include <Util/Vector.h>

class WoodletJump;

namespace UI {

class Credits : public UI {
public:
    Credits(WoodletJump &game, float ui_scale);
    void init(sf::Font &font);
    void build(Vector2i window_size);
private:
    static constexpr Vector2i kCreditsViewDefaultSize = {450, 190};
    static constexpr const char *kCreditsText = "Player avatar: GNU Image Manipulation Program (GIMP)\n\n"
            "Platform graphics:\n"
            "https://craftpix.net/freebies/free-medieval-ruins-cartoon-2d-tileset/\n"
            "https://craftpix.net/file-licenses/\n\n"
            "Programming APIs:\n"
            "Window creation, image loading, text rendering: SFML library\n"
            "Other graphics: OpenGL API, GLSL\n"
            "Matrix mathematics: GLM library";

    WoodletJump &game_;
    ButtonID credits_view_;
    ButtonID back_button_;
};

}
