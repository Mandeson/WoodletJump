#pragma once

#include <exception>
#include <string>
#include <SFML/OpenGL.hpp>

class Texture {
public:
class LoadingError : public std::exception {
    public:
        const char* what() const noexcept override;
    };

    class NotLoaded : public std::exception {
    public:
        const char* what() const noexcept override;
    };

    void load(const char *name);
    void bind();
private:
    bool loaded_{};
    GLuint id_{};
};
