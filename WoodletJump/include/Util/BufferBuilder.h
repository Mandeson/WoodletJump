#pragma once

#include <vector>
#include <SFML/OpenGL.hpp>
#include <Util/Vector.h>
#include <Util/TextureRect.h>

class BufferBuilder {
public:
    BufferBuilder();
    ~BufferBuilder();
    void addRectangle(Vector2f pos, Vector2f size, const TextureRect& texture_rect);
    void upload(GLenum usage=GL_STATIC_DRAW);

    /* Binds buffer objects and enables their attributes
     * args: location of position and texture coordinate attributes within a ahader
     */
    void bind(GLuint aPosLocation, GLuint aTexCoordLocation);
    int getElementCount();
private:
    std::vector<float> vertices_;
    std::vector<unsigned int> indices_;
    unsigned int indice_index_{};
    GLuint VBO_;
    GLuint EBO_;
    bool uploaded_{};
};
