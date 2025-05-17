#pragma once

#include <exception>
#include <string>
#include <SFML/OpenGL.hpp>

class Texture {
public:
class FileNotFoundError : public std::exception {
    public:
        FileNotFoundError(std::string &&filename);
        const char* what() const noexcept override;
        const std::string &getFilename();
    private:
        std::string filename_;
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
