#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class Application {
public:
    void run();
private:
    static constexpr double kMaxFrameDelay = 2.0;

    sf::RenderWindow window_;
};
