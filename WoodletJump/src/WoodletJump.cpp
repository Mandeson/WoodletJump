#include <iostream>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Image.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <WoodletJump.h>
#include <Logger.h>

WoodletJump::WoodletJump(sf::RenderWindow &window, float ui_scale) : random_device_{}, random_(random_device_()),
        window_(window), player_(), world_(), ui_pause_(*this, ui_scale), ui_controls_(*this, ui_scale), ui_game_over_(*this, ui_scale), last_score_(-1) {
    if (!font_.openFromFile("fonts/Roboto-Regular.ttf")) {
        throw WoodletJump::InitError();
    }
    ui_pause_.init(font_);
    ui_controls_.init(font_);
    ui_game_over_.init(font_);
    sf::Text &score_text = score_text_.emplace(font_); // constructor requires a complete font object
    score_text.setCharacterSize(20 * ui_scale);
    score_text.setPosition({10.0f * ui_scale, 5.0f * ui_scale});
    try {
        texture_.load("atlas.png");
    } catch (Texture::LoadingError &e) {
        Logger::log(Logger::MessageType::kError, e.what());
        throw WoodletJump::InitError();
    }
    try {
        sprite_renderer_.init();
        scene_renderer_.init();
        color_renderer_.init();
    } catch (Shader::FileNotFoundError &e) {
        Logger::log(Logger::MessageType::kError, std::string(e.what()) + ": " + e.getFilename());
        throw WoodletJump::InitError();
    } catch (Shader::CompileError &e) {
        Logger::log(Logger::MessageType::kError, std::string(e.what()) + ": " + e.getFilename()
                + '\n' + e.getCompileError());
        throw WoodletJump::InitError();
    } catch (Shader::LinkError &e) {
        Logger::log(Logger::MessageType::kError, std::string(e.what()) + ": " + e.getName()
                + '\n' + e.getLinkError());
        throw WoodletJump::InitError();
    }

    player_.init();
}

void WoodletJump::windowSize(Vector2i size) {
    window_size_ = size;
    sprite_renderer_.windowSize(size);
    scene_renderer_.windowSize(size);
    color_renderer_.windowSize(size);
    camera_.windowSize(size);
    ui_pause_.build(size);
    ui_controls_.build(size);
    ui_game_over_.build(size);
}

void WoodletJump::render()
{
    window_.clear(sf::Color::Black);

    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    background_.render(color_renderer_, window_size_);

    texture_.bind();

    auto &scene_buffer_builder = scene_renderer_.getBufferBuilder();
    scene_buffer_builder.clear();
    world_.generate(random_, camera_);
    world_.buildMesh(scene_buffer_builder, window_size_, camera_);
    scene_renderer_.render();
    player_.render(sprite_renderer_, window_size_, camera_);

    if (active_ui_)
        active_ui_->render(color_renderer_);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    int score = std::max(0, static_cast<int>(player_.getWorldPosition() * 10));
    sf::Text &score_text = score_text_.value();
    if (last_score_ != score) {
        score_text.setString(std::to_string(score));
        last_score_ = score;
    }
    window_.draw(score_text);
    
    if (active_ui_) {
        active_ui_->renderText(window_);
        if (active_ui_ == &ui_game_over_)
            ui_game_over_.renderGameOver(window_);
    }
    
    glDisable(GL_BLEND);
}

void WoodletJump::timeStep(double d_time) {
    if (active_ui_ == nullptr) {
        player_.timeStep(d_time, world_, camera_);
        if (player_.gameOver()) {
            active_ui_ = &ui_game_over_;
        }
    }
}

void WoodletJump::keyPressed(sf::Keyboard::Key key) {
    switch (key) {
    case sf::Keyboard::Key::Escape:
        if (active_ui_ == &ui_pause_)
            active_ui_ = nullptr;
        else if (active_ui_ == &ui_controls_)
            active_ui_ = &ui_pause_;
        else if (active_ui_ == nullptr)
            active_ui_ = &ui_pause_;
        break;
    default:
        break;
    }
}

void WoodletJump::mouseClick(Vector2i position, sf::Mouse::Button button) {
    if (active_ui_)
        active_ui_->mouseClick(position, button);
}
