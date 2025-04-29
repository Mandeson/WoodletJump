#include <iostream>
#include <SFML/OpenGL.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <WoodletJump.h>

WoodletJump::WoodletJump() {
    const char *filename = "textures/atlas.png";
    if (!texture_.loadFromFile(filename))
        throw WoodletJump::InitError();
    texture_.setSmooth(true);
    try {
        shader_.load("sprite");
    } catch (Shader::FileNotFoundError& e) {
        std::cerr << e.what() << ": " << e.getFilename()
                << std::endl;
        throw WoodletJump::InitError();
    } catch (Shader::CompileError& e) {
        std::cerr << e.what() << ": " << e.getFilename()
                << std::endl << e.getCompileError();
        throw WoodletJump::InitError();
    } catch (Shader::LinkError &e) {
        std::cerr << e.what() << ": '" << e.getName()
                << '\'' << std::endl << e.getLinkError();
        throw WoodletJump::InitError();
    }
    aPosLocation_ = shader_.getAttribLocation("aPos");
    aTexCoordLocation_ = shader_.getAttribLocation("aTexCoord");
    uTransformLocation_ = shader_.getUniformLocation("uTransform");
    buffer_builder_.addRectangle({0, 0}, {512, 512});
    buffer_builder_.upload();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void WoodletJump::windowSize(Vector2i size) {
    projection_ = glm::ortho(0.0f, static_cast<float>(size.x), static_cast<float>(size.y), 0.0f);
}

void WoodletJump::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    buffer_builder_.bind(aPosLocation_, aTexCoordLocation_);
    shader_.use();
    shader_.setUniformMat4(uTransformLocation_, projection_);
    sf::Texture::bind(&texture_);
    glDrawElements(GL_TRIANGLES, buffer_builder_.getElementCount(), GL_UNSIGNED_INT, 0);
    Shader::reset();
}
