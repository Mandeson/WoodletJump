#include <iostream>
#include <SFML/OpenGL.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <WoodletJump.h>
#include <Logger.h>

WoodletJump::WoodletJump() : player_(), world_() {
    if (!texture_.loadFromFile("textures/atlas.png"))
        throw WoodletJump::InitError();
    texture_.setSmooth(true);
    static_cast<void>(texture_.generateMipmap());
    try {
        sprite_renderer_.init();
        scene_renderer_.init();
    } catch (Shader::FileNotFoundError& e) {
        Logger::log(Logger::MessageType::kError, std::string(e.what()) + ": " + e.getFilename());
        throw WoodletJump::InitError();
    } catch (Shader::CompileError& e) {
        Logger::log(Logger::MessageType::kError, std::string(e.what()) + ": " + e.getFilename()
                + '\n' + e.getCompileError());
        throw WoodletJump::InitError();
    } catch (Shader::LinkError &e) {
        Logger::log(Logger::MessageType::kError, std::string(e.what()) + ": " + e.getName()
                + '\n' + e.getLinkError());
        throw WoodletJump::InitError();
    }

    player_.init();
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void WoodletJump::windowSize(Vector2i size) {
    window_size_ = size;
    sprite_renderer_.windowSize(size);
    scene_renderer_.windowSize(size);
}

void WoodletJump::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    sf::Texture::bind(&texture_);

    auto &scene_buffer_builder = scene_renderer_.getBufferBuilder();
    scene_buffer_builder.clear();
    world_.buildMesh(scene_buffer_builder, window_size_);
    scene_renderer_.render();

    player_.render(sprite_renderer_, window_size_);
    
    glDisable(GL_BLEND);
}
