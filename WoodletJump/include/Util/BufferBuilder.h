#pragma once

#include <vector>
#include <SFML/OpenGL.hpp>
#include <Util/Vector.h>
#include <Util/TextureRect.h>
#include <Util/Color.h>

class BufferBuilderBase {
public:
    BufferBuilderBase();
    ~BufferBuilderBase();
    void clear();
    void upload(GLenum usage=GL_STATIC_DRAW);
    int getElementCount();
    static void reset(GLuint aPosLocation, GLuint aSecondAttribLocation);
protected:
    std::vector<float> vertices_;
    std::vector<unsigned int> indices_;
    unsigned int indice_index_{};
    int allocated_size_{};
    GLuint VBO_;
    GLuint EBO_;
    bool uploaded_{};
};

class TextureBufferBuilder : public BufferBuilderBase {
public:
    void addRectangle(Vector2f pos, Vector2f size, const TextureRect& texture_rect);
    /* Binds buffer objects and enables their attributes
       args: location of position and texture coordinate attributes within a ahader */
    void bind(GLuint aPosLocation, GLuint aTexCoordLocation);
    /* Resets global OpenGL state and disables given attribute arrays.
       Use after rendering to avoid interfering with legacy OpenGL code */
    static void reset(GLuint aPosLocation, GLuint aTexCoordLocation);
};

class ColorBufferBuilder : public BufferBuilderBase {
public:
    void addRectangle(Vector2f pos, Vector2f size, Color color);
    void addGradient(Vector2f pos, Vector2f size, Color color_a, Color color_b);
    /* Binds buffer objects and enables their attributes
       args: location of position and color attributes within a ahader */
    void bind(GLuint aPosLocation, GLuint aColorLocation);
    /* Resets global OpenGL state and disables given attribute arrays.
       Use after rendering to avoid interfering with legacy OpenGL code */
    static void reset(GLuint aPosLocation, GLuint aColorLocation);
};
