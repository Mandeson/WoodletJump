#include <memory>
#include <Application.h>
#include <SFML/OpenGL.hpp>
#include <WoodletJump.h>
#include <Logger.h>
#include <chrono>

constexpr sf::Vector2u kInitialWindowSize = {800, 600};

void Application::run() {
    window_.create(sf::VideoMode(kInitialWindowSize), "WoodletJump");
    window_.setVerticalSyncEnabled(true);

    auto monitor_height = sf::VideoMode::getDesktopMode().size.y;
    float ui_scale = monitor_height / 600.0f;

    try {
        std::unique_ptr<WoodletJump> game_ = std::make_unique<WoodletJump>(window_, ui_scale);

        game_->windowSize({static_cast<int>(kInitialWindowSize.x),
            static_cast<int>(kInitialWindowSize.y)});

        std::optional<std::chrono::high_resolution_clock::time_point> time;

        while (window_.isOpen())
        {
            while (const std::optional event = window_.pollEvent())
            {
                if (event->is<sf::Event::Closed>()) {
                    return;
                } else if (const auto* resized = event->getIf<sf::Event::Resized>()) {
                    auto [x, y] = resized->size;
                    window_.setView(sf::View(sf::FloatRect({0.0f, 0.0f}, {static_cast<float>(x), static_cast<float>(y)})));
                    glViewport(0, 0, x, y);
                    game_->windowSize({static_cast<int>(x), static_cast<int>(y)});
                } else if (const auto* key_pressed = event->getIf<sf::Event::KeyPressed>()) {
                    game_->keyPressed(key_pressed->code);
                } else if (const auto* mouse_button_pressed = event->getIf<sf::Event::MouseButtonReleased>()) {
                    game_->mouseClick({mouse_button_pressed->position.x, mouse_button_pressed->position.y}, mouse_button_pressed->button);
                }
            }

            if (!time.has_value()) {
                time = std::chrono::high_resolution_clock::now();
            } else {
                auto now_time = std::chrono::high_resolution_clock::now();
                auto duration = now_time - time.value();
                double d_time = std::chrono::duration<double>(duration).count();
                if (d_time < kMaxFrameDelay) {
                    while (d_time > WoodletJump::kMaxTimeStep) {
                        game_->timeStep(WoodletJump::kMaxTimeStep);
                        d_time -= WoodletJump::kMaxTimeStep;
                    }
                    game_->timeStep(d_time);
                }
                time = now_time;
            }

            game_->render();

            window_.display();
        }
    } catch (std::exception &e) {
        Logger::log(Logger::MessageType::kError, e.what());
    }
}
