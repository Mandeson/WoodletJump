#include <iostream>
#include <Application.h>
#include <SFML/OpenGL.hpp>
#include <WoodletJump.h>
#include <Logger.h>

constexpr sf::Vector2u kInitialWindowSize = {800, 600};

void Application::run() {
    window_.create(sf::VideoMode(kInitialWindowSize), "WoodletJump");
    window_.setVerticalSyncEnabled(true);

    try {
        std::unique_ptr<WoodletJump> game_ = std::make_unique<WoodletJump>();

        game_->windowSize({static_cast<int>(kInitialWindowSize.x),
            static_cast<int>(kInitialWindowSize.y)});

        while (window_.isOpen())
        {
            while (const std::optional event = window_.pollEvent())
            {
                if (event->is<sf::Event::Closed>()) {
                    return;
                } else if (const auto* resized = event->getIf<sf::Event::Resized>()) {
                    auto [x, y] = resized->size;
                    glViewport(0, 0, x, y);
                    game_->windowSize({static_cast<int>(x), static_cast<int>(y)});
                }
            }

            game_->render();

            window_.display();
        }
    } catch (std::exception &e) {
        Logger::log(Logger::MessageType::kError, e.what());
    }
}
