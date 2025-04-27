#include <fstream>
#include <filesystem>
#include <Shader.h>
#include <SFML/OpenGL.hpp>

Shader::FileNotFoundError::FileNotFoundError(std::string&& filename) : filename_(filename) { }

const char* Shader::FileNotFoundError::what() const noexcept {
    return "Shader: file not found";
}

const std::string& Shader::FileNotFoundError::getFilename() {
    return filename_;
}

Shader::CompileError::CompileError(std::string&& filename, std::string&& compile_error)
        : filename_(filename), compile_error_(compile_error) { }

const char* Shader::CompileError::what() const noexcept {
    return "Shader: compilation error";
}

const std::string&  Shader::CompileError::getFilename() {
    return filename_;
}

const std::string&  Shader::CompileError::getCompileError() {
    return compile_error_;
}

Shader::LinkError::LinkError(std::string &&name, std::string &&link_error)
        : name_(name), link_error_(link_error) { }

const char* Shader::LinkError::what() const noexcept {
    return "Shader: link error";
}

const std::string& Shader::LinkError::getName() {
    return name_;
}

const std::string& Shader::LinkError::getLinkError() {
    return link_error_;
}

Shader::~Shader() {
    if (id_)
        glDeleteProgram(id_);
}

static inline std::string _load_file(std::string& filename) {
    auto size = std::filesystem::file_size(filename);
    std::string text(size, '\0');
    std::ifstream in(filename);
    if (in.fail())
        throw Shader::FileNotFoundError(std::move(filename));
    in.read(&text[0], size);
    return text;
}

static GLuint _compile(std::string&& filename, GLenum type)
{
    std::string text = _load_file(filename);
    const GLchar* text_c_str = text.c_str();
    GLuint shader = glCreateShader(type);
    if (shader == 0)
        throw std::runtime_error("Could not create an OpenGL Shader object");
    glShaderSource(shader, 1, &text_c_str, 0);
    glCompileShader(shader);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLsizei error_msg_size;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &error_msg_size);
        std::string error_msg(error_msg_size, '\0');
        glGetShaderInfoLog(shader, error_msg_size, nullptr, &error_msg[0]);
        throw Shader::CompileError(std::move(filename), std::move(error_msg));
    }
    return shader;
}

void Shader::load(const char *name) {
    id_ = glCreateProgram();
    if (id_ == 0)
        throw std::runtime_error("Could not create an OpenGL Program object");

    GLuint vertex = _compile(std::string("shaders/") + name + ".vs", GL_VERTEX_SHADER);
    glAttachShader(id_, vertex);
    glDeleteShader(vertex);

    GLuint fragment = _compile(std::string("shaders/") + name + ".fs", GL_FRAGMENT_SHADER);
    glAttachShader(id_, fragment);
    glDeleteShader(fragment);

    glLinkProgram(id_);
    GLint status;
    glGetProgramiv(id_, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLsizei error_msg_size;
        glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &error_msg_size);
        std::string error_msg(error_msg_size, '\0');
        glGetProgramInfoLog(id_, error_msg_size, nullptr, &error_msg[0]);
        throw Shader::LinkError(std::string(name), std::move(error_msg));
    }
}
