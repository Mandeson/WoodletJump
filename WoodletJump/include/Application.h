#pragma once

#include <memory>
#include <SFML/Window.hpp>
#include <WoodletJump.h>

class Application {
public:
    void run();
private:
    sf::Window window_;
    std::unique_ptr<WoodletJump> game;
};
