#include <UI/UI.h>

namespace UI {

const char* UI::NotInitialised::what() const noexcept {
    return "UI: using UI that is not initialised";
}    

UI::Button::Button(sf::Font &font, uint32_t text_height, const std::string &text, std::function<void()> callback)
        : text_(font, text), text_height_(text_height), callback_(callback) {
    text_.setCharacterSize(text_height);
    text_.setFillColor(sf::Color::White);
    float origin = text_.getGlobalBounds().size.x / 2.f + text_.getLocalBounds().position.x;
    text_.setOrigin({std::round(origin), 0.0f});
}

void UI::Button::setBounds(BoxI bounds) {
    bounds_.position.x = static_cast<float>(bounds.position.x);
    bounds_.position.y = static_cast<float>(bounds.position.y);
    bounds_.size.x = static_cast<float>(bounds.size.x);
    bounds_.size.y = static_cast<float>(bounds.size.y);
    text_.setPosition({bounds_.position.x + bounds.size.x / 2, bounds_.position.y + bounds.size.y / 2 - text_height_ / 3 * 2});
}

UI::UI(float ui_scale) : ui_scale_(ui_scale) {
    text_height_ = static_cast<uint32_t>(kDefaultFontSize * ui_scale);
}

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

void UI::mouseClick(Vector2i position, sf::Mouse::Button button) {
    if (button == sf::Mouse::Button::Left) {
        for (const auto &button : buttons_) {
            auto b_position = button.bounds_.position;
            auto b_size = button.bounds_.size;
            if (position.x >= b_position.x && position.x < b_position.x + b_size.x && position.y >= b_position.y
                    && position.y < b_position.y + b_size.y) {
                if (button.callback_ != nullptr)
                    button.callback_();
            }
        }
    }
}

UI::ButtonID UI::addButton(const std::string &text, std::function<void()> callback) {
    if (!initialised())
        throw UI::NotInitialised();
    buttons_.emplace_back(*font_, text_height_, text, callback);
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
