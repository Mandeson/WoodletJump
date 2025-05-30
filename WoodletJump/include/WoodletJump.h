#pragma once

#include <exception>
#include <random>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <Shader.h>
#include <Texture.h>
#include <glm/glm.hpp>
#include <Util/Vector.h>
#include <Util/BufferBuilder.h>
#include <Renderer/SpriteRenderer.h>
#include <Renderer/SceneRenderer.h>
#include <Renderer/ColorRenderer.h>
#include <World/World.h>
#include <Player.h>
#include <Camera.h>
#include <UI/Pause.h>
#include <UI/GameOver.h>

class WoodletJump {
public:
    class InitError : public std::exception {
    public:
        const char* what() const noexcept override {
            return "Initialisation failed";
        }
    };

    static constexpr double kMaxTimeStep = 0.1;

    // Throws WoodletJump::InitError if not properly initialised
    WoodletJump(sf::RenderWindow &window, float ui_scale);
    // Called after constructor and every time the window size changes
    void windowSize(Vector2i size);
    void render();
    void timeStep(double d_time);
    void keyPressed(sf::Keyboard::Key key);
    void mouseClick(Vector2i position, sf::Mouse::Button button);
private:
    friend class UI::Pause;
    friend class UI::GameOver;

    std::random_device random_device_;
    std::mt19937 random_;
    sf::RenderWindow &window_;
    Vector2i window_size_;
    sf::Font font_;
    Texture texture_;
    Renderer::SpriteRenderer sprite_renderer_;
    Renderer::SceneRenderer scene_renderer_;
    Renderer::ColorRenderer color_renderer_;
    Player player_;
    World::World world_;
    Camera camera_;
    UI::Pause ui_pause_;
    UI::GameOver ui_game_over_;
    UI::UI *active_ui_{};
};
