#pragma once

#include <vector>
#include <cstdint>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Util/Box.h>
#include <Util/BufferBuilder.h>
#include <Renderer/ColorRenderer.h>

namespace UI {

class UI {
public:
    using ButtonID = uint32_t;
    class Button {
    public:
        Button(sf::Font &font, uint32_t text_height, const std::string &text);
        void setBounds(BoxI bounds);
    private:
        static constexpr Color kColor = Color{64, 64, 64, 255};
        static constexpr Color kInteriorColor = Color{96, 96, 96, 255};

        friend class UI;

        sf::Text text_;
        Box bounds_;
        uint32_t text_height_;
    };

    class NotInitialised : public std::exception {
    public:
        const char* what() const noexcept override;
    };

    UI(float ui_scale);
    void render(Renderer::ColorRenderer &color_renderer);
    void renderText(sf::RenderWindow &window);
protected:
    void init(sf::Font &font);
    void build();
    ButtonID addButton(const std::string &text);
    Button &getButton(ButtonID button_id);
    float getUIScale();
private:
    bool initialised();

    static constexpr int kDefaultFontSize = 15;

    float ui_scale_;
    uint32_t text_height_;
    sf::Font *font_{};
    std::vector<Button> buttons_;
    ColorBufferBuilder buffer_builder_;
};

}
