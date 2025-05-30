#include <cmath>
#include <UI/UI.h>

namespace UI {

const char* UI::NotInitialised::what() const noexcept {
    return "UI: using UI that is not initialised";
}    

UI::Button::Button(sf::Font &font, float ui_scale, const std::string &text) : text_(font, text) {
    text_.setCharacterSize(static_cast<unsigned int>(kDefaultFontSize * ui_scale));
    text_.setFillColor(sf::Color::White);
    auto origin = text_.getGlobalBounds().size / 2.f + text_.getLocalBounds().position;
    text_.setOrigin({roundf(origin.x), roundf(origin.y)});
}

void UI::Button::setBounds(BoxI bounds) {
    bounds_.position.x = static_cast<float>(bounds.position.x);
    bounds_.position.y = static_cast<float>(bounds.position.y);
    bounds_.size.x = static_cast<float>(bounds.size.x);
    bounds_.size.y = static_cast<float>(bounds.size.y);
    text_.setPosition({bounds_.position.x + bounds.size.x / 2, bounds_.position.y + bounds.size.y / 2});
}

UI::UI(float ui_scale) : ui_scale_(ui_scale) { }

void UI::init(sf::Font &font) {
    font_ = &font;
}

void UI::build() {
    buffer_builder_.clear();
    for (const auto &button : buttons_) {
        auto position = button.bounds_.position;
        auto size = button.bounds_.size;
        buffer_builder_.addRectangle(position, size, Button::kColor);
        buffer_builder_.addRectangle({position.x + 2, position.y + 2}, {size.x - 2 * 2, size.y - 2 * 2}, Button::kInteriorColor);
    }
    buffer_builder_.upload(GL_DYNAMIC_DRAW);
}

void UI::render(Renderer::ColorRenderer &color_renderer) {
    color_renderer.render(buffer_builder_);
}

void UI::renderText(sf::RenderWindow &window) {
    if (!initialised())
        throw UI::NotInitialised();
    for (auto &button : buttons_)
        window.draw(button.text_);
}

UI::ButtonID UI::addButton(const std::string &text) {
    if (!initialised())
        throw UI::NotInitialised();
    buttons_.emplace_back(*font_, ui_scale_, text);
    return static_cast<uint32_t>(buttons_.size() - 1);
}

UI::Button &UI::getButton(UI::ButtonID button_id) {
    if (!initialised())
        throw UI::NotInitialised();
    return buttons_.at(button_id);
}

float UI::getUIScale() {
    return ui_scale_;
}

bool UI::initialised() {
    return font_ != nullptr;
}

}
