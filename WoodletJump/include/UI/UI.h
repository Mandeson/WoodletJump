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
    class Button {
    public:
        Button(sf::Font &font, float ui_scale, const std::string &text);
        void setBounds(BoxI bounds);
    private:
        static constexpr Color kColor = Color{64, 64, 64, 255};
        static constexpr Color kInteriorColor = Color{96, 96, 96, 255};

        friend class UI;

        sf::Text text_;
        Box bounds_;
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
    Button *addButton(const std::string &text);
    float getUIScale();
private:
    static constexpr int kDefaultFontSize = 15;

    float ui_scale_;
    sf::Font *font_{};
    std::vector<Button> buttons_;
    ColorBufferBuilder buffer_builder_;
};

}
