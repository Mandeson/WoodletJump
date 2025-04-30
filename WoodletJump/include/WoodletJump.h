#pragma once

#include <exception>
#include <Shader.h>
#include <glm/glm.hpp>
#include <Util/Vector.h>
#include <Util/BufferBuilder.h>
#include <SFML/Graphics/Texture.hpp>
#include <Sprite.h>

class WoodletJump {
public:
    class InitError : std::exception {
    public:
        const char* what() const noexcept override {
            return "Initialisation failed";
        }
    };

    // Throws WoodletJump::InitError if not properly initialised
    WoodletJump();
    // Called after constructor and every time the window size changes
    void windowSize(Vector2i size);
    void render();
private:
    Renderer::SpriteRenderer sprite_renderer_;
    sf::Texture texture_;
    Sprite sprite_;
};
