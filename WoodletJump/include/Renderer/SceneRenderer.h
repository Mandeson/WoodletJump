#pragma once

#include <SFML/OpenGL.hpp>
#include <Shader.h>
#include <Util/Vector.h>
#include <Util/BufferBuilder.h>

namespace Renderer {

class SceneRenderer {
public:
    void init();
    void windowSize(Vector2i size);
    TextureBufferBuilder& getBufferBuilder();
    void render();
private:
    Shader shader_;
    TextureBufferBuilder buffer_builder_;
    GLuint aPosLocation_;
    GLuint aTexCoordLocation_;
    GLuint uWindowSizeLocation_;
};

};
