#pragma once

#include <exception>
#include <Shader.h>
#include <glm/glm.hpp>
#include <Util/Vector.h>
#include <Util/BufferBuilder.h>
#include <SFML/Graphics/Texture.hpp>
#include <Renderer/SpriteRenderer.h>
#include <Renderer/SceneRenderer.h>
#include <World/World.h>
#include <Player.h>

class WoodletJump {
public:
    class InitError : public std::exception {
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
    Vector2i window_size_;
    sf::Texture texture_;
    Renderer::SpriteRenderer sprite_renderer_;
    Renderer::SceneRenderer scene_renderer_;
    Player player_;
    World::World world_;
};
