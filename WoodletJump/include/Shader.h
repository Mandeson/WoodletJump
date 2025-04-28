#pragma once

#include <string>
#include <exception>
#include <SFML/OpenGL.hpp>

class Shader {
public:
    class FileNotFoundError : std::exception {
    public:
        FileNotFoundError(std::string&& filename);
        const char* what() const noexcept override;
        const std::string& getFilename();
    private:
        std::string filename_;
    };

    class CompileError : std::exception {
    public:
        CompileError(std::string&& filename, std::string&& compile_error);
        const char* what() const noexcept override;
        const std::string& getFilename();
        const std::string& getCompileError();
    private:
        std::string filename_;
        std::string compile_error_;
    };

    class LinkError : std::exception {
    public:
        LinkError(std::string&& name, std::string&& link_error);
        const char* what() const noexcept override;
        const std::string& getName();
        const std::string& getLinkError();
    private:
        std::string name_;
        std::string link_error_;
    };

    Shader(const Shader&) = delete; // non-copyable
    Shader& operator=(const Shader&) = delete;
    ~Shader();

    /* Load the shader from disk and compile with OpenGL
     * Must be called from the opengl context thread
     */
    void load(const char *filename);
private:
    GLuint id_{};
};
