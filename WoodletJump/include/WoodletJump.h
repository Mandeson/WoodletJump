#pragma once

#include <exception>
#include <Shader.h>
#include <glm/glm.hpp>
#include <Util/Vector.h>
#include <Util/BufferBuilder.h>
#include <SFML/Graphics/Texture.hpp>

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
    // Called after constructor and every time the window size changes
    void windowSize(Vector2i size);
    void render();
private:
    sf::Texture texture_;
    Shader shader_;
    BufferBuilder buffer_builder_;
    GLuint aPosLocation_;
    GLuint aTexCoordLocation_;
    GLuint uTransformLocation_;
    glm::mat4 projection_;
};
