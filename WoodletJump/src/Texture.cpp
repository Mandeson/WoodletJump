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

    // Texture alpha premultiplication (prevents graphical glitches when blending)
    for (uint32_t y = 0; y < image.getSize().y; y++) {
        for (uint32_t x = 0; x < image.getSize().x; x++) {
            auto color = image.getPixel({x, y});
            float alpha = static_cast<float>(color.a) / 255;
            color.r = static_cast<uint8_t>(color.r * alpha);
            color.g = static_cast<uint8_t>(color.g * alpha);
            color.b = static_cast<uint8_t>(color.b * alpha);
            image.setPixel({x, y}, color);
        }
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
            GL_UNSIGNED_BYTE, reinterpret_cast<const void *>(image.getPixelsPtr()));
        
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
