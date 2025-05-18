#include <SFML/Graphics/Image.hpp>
#include <Texture.h>
#include <Logger.h>

const char *Texture::LoadingError::what() const noexcept {
    return "Texture: loading error";
}

const char* Texture::NotLoaded::what() const noexcept {
    return "Texture: using a texture that is not loaded";
}

void Texture::load(const char *name) {
    std::string filename = std::string("textures/") + name;
    sf::Image image;
    if (!image.loadFromFile(filename))
        throw LoadingError();

    auto buffer = const_cast<std::uint8_t *>(image.getPixelsPtr());
    // Texture alpha premultiplication (prevents graphical glitches when blending)
    for (uint32_t i = 0; i < image.getSize().x * image.getSize().y * 4 - 1; i += 4) {
        float a = (float)buffer[i + 3] / 255;
        buffer[i] = (uint8_t)(buffer[i] * a);
        buffer[i + 1] = (uint8_t)(buffer[i + 1] * a);
        buffer[i + 2] = (uint8_t)(buffer[i + 2] * a);
    }

    glGenTextures(1, &id_);

    glBindTexture(GL_TEXTURE_2D, id_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

#ifndef USE_GLES2
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); // OpenGL 2.1
#endif

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA,
            GL_UNSIGNED_BYTE, buffer);
        
#ifdef USE_GLES2
    glGenerateMipmap(GL_TEXTURE_2D); // requires OpenGL 3.0 or GLES 2.0
#endif

    loaded_ = true;
}

void Texture::bind() {
    if (!loaded_)
        throw NotLoaded();
    
    glBindTexture(GL_TEXTURE_2D, id_);
}
