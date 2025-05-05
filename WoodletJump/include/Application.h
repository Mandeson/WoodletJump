#pragma once

#include <memory>
#include <SFML/Window.hpp>

class Application {
public:
    void run();
private:
    sf::Window window_;
};
