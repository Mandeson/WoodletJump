#include <iostream>
#include <Application.h>
#include <SFML/OpenGL.hpp>

constexpr sf::Vector2u kInitialWindowSize = {800, 600};

void Application::run() {
    window_.create(sf::VideoMode(kInitialWindowSize), "WoodletJump");
    window_.setVerticalSyncEnabled(true);

    try {
        game_ = std::make_unique<WoodletJump>();
    } catch (WoodletJump::InitError &e) {
        std::cerr << e.what() << std::endl;
        window_.close();
        return;
    }

    game_->windowSize({static_cast<int>(kInitialWindowSize.x),
            static_cast<int>(kInitialWindowSize.y)});

    while (window_.isOpen())
    {
        while (const std::optional event = window_.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                game_.reset();
                window_.close();
                return;
            }
            else if (const auto* resized = event->getIf<sf::Event::Resized>()) {
                auto [x, y] = resized->size;
                glViewport(0, 0, x, y);
                game_->windowSize({static_cast<int>(x), static_cast<int>(y)});
            }
        }

        game_->render();

        window_.display();
    }
}
