#pragma once

#include <vector>
#include <SFML/OpenGL.hpp>
#include <Util/Vector.h>

class BufferBuilder {
public:
    BufferBuilder();
    ~BufferBuilder();
    void addRectangle(Vector2f pos, Vector2f size);
    void upload(GLenum usage=GL_STATIC_DRAW);

    /* Binds buffer objects and enables their attributes
     * args: location of position attribute within a ahader
     */
    void bind(GLuint aPosLocation);
private:
    std::vector<float> vertices_;
    std::vector<unsigned int> indices_;
    unsigned int indice_index_{};
    GLuint VBO_;
    GLuint EBO_;
    bool uploaded_{};
};
