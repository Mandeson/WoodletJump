#include <iostream>
#include <Application.h>
#include <SFML/OpenGL.hpp>

void Application::run() {
    window_.create(sf::VideoMode({800, 600}), "WoodletJump");
    window_.setVerticalSyncEnabled(true);

    try {
        game_ = std::make_unique<WoodletJump>();
    } catch (WoodletJump::InitError &e) {
        std::cerr << e.what() << std::endl;
        window_.close();
        return;
    }

    while (window_.isOpen())
    {
        while (const std::optional event = window_.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                window_.close();
            }
            else if (const auto* resized = event->getIf<sf::Event::Resized>())
                glViewport(0, 0, resized->size.x, resized->size.y);
        }

        game_->render();

        window_.display();
    }
}
