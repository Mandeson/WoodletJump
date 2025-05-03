#include <iostream>
#include <SFML/OpenGL.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <WoodletJump.h>

WoodletJump::WoodletJump() {
    const char *filename = "textures/atlas.png";
    if (!texture_.loadFromFile(filename))
        throw WoodletJump::InitError();
    texture_.setSmooth(true);
    static_cast<void>(texture_.generateMipmap());
    try {
        sprite_renderer_.init();
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
    sprite_.init(TextureRect(texture_.getSize().x, {0, 0}, {80, 80}));
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void WoodletJump::windowSize(Vector2i size) {
    sprite_.setSize({static_cast<float>(size.y / 10), static_cast<float>(size.y / 10)});
    sprite_.setPosition({static_cast<float>(size.x / 2), static_cast<float>(size.y / 2)});
    sprite_renderer_.windowSize(size);
}

void WoodletJump::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    sf::Texture::bind(&texture_);
    sprite_renderer_.render(sprite_);
    
    glDisable(GL_BLEND);
}
