#include <iostream>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Image.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <WoodletJump.h>
#include <Logger.h>

WoodletJump::WoodletJump(sf::RenderWindow &window) : random_device_{}, random_(random_device_()),
        window_(window), player_(), world_() {
    if (!font_.openFromFile("fonts/Roboto-Regular.ttf")) {
        throw WoodletJump::InitError();
    }
    text_ = std::make_unique<sf::Text>(font_, "Hello World");
    text_->setCharacterSize(24);
    text_->setFillColor(sf::Color::Black);
    try {
        texture_.load("atlas.png");
    } catch (Texture::LoadingError &e) {
        Logger::log(Logger::MessageType::kError, e.what());
        throw WoodletJump::InitError();
    }
    try {
        sprite_renderer_.init();
        scene_renderer_.init();
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
    
    glClearColor(0.5f, 0.6f, 0.9f, 1.0f);
}

void WoodletJump::windowSize(Vector2i size) {
    window_size_ = size;
    sprite_renderer_.windowSize(size);
    scene_renderer_.windowSize(size);
    camera_.windowSize(size);
}

void WoodletJump::render()
{
    window_.clear(sf::Color{60, 180, 80});

    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    texture_.bind();

    auto &scene_buffer_builder = scene_renderer_.getBufferBuilder();
    scene_buffer_builder.clear();
    world_.generate(random_, camera_);
    world_.buildMesh(scene_buffer_builder, window_size_, camera_);
    scene_renderer_.render();
    player_.render(sprite_renderer_, window_size_, camera_);

    window_.draw(*text_);
    
    glDisable(GL_BLEND);
}

void WoodletJump::timeStep(double d_time) {
    player_.timeStep(d_time, world_, camera_);
}
