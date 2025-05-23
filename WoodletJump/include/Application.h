#pragma once

#include <memory>
#include <SFML/Window.hpp>

class Application {
public:
    void run();
private:
    static constexpr double kMaxFrameDelay = 2.0;

    sf::Window window_;
};
