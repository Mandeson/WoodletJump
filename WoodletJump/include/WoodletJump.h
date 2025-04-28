#pragma once

#include <exception>

class WoodletJump {
public:
    class InitError : std::exception {
    public:
        const char* what() const noexcept override {
            return "Initialisation failed";
        }
    };

    // Throws WoodletJump::InitError if not properly initialised
    WoodletJump();
    void render();
private:
};
