#pragma once

#include <string>
#include <exception>
#include <SFML/OpenGL.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Util/Vector.h>

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

    class NotLoaded : std::exception {
    public:
        const char* what() const noexcept override;
    };

    Shader();
    Shader(const Shader&) = delete; // non-copyable
    Shader& operator=(const Shader&) = delete;
    ~Shader();

    /* Load the shader from disk and compile with OpenGL
     * Must be called from the opengl context thread
     */
    void load(const char *filename);
    void use();
    GLuint getAttribLocation(const char* name);
    GLuint getUniformLocation(const char* name);
    void setUniformMat4(GLuint uniform_location, glm::mat4 matrix);
    void setUniform2f(GLuint uniform_location, Vector2f vec);;
    // Bind the default OpenGL shader
    static void reset();
private:
    GLuint id_{};
};
