#include <Application.h>
#include <SFML/OpenGL.hpp>

void Application::run() {
    window_.create(sf::VideoMode({800, 600}), "OpenGL");

    while (window_.isOpen())
    {
        while (const std::optional event = window_.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window_.close();
            else if (const auto* resized = event->getIf<sf::Event::Resized>())
                glViewport(0, 0, resized->size.x, resized->size.y);
        }

        // TODO: render

        window_.display();
    }
}
