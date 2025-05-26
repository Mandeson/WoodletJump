#pragma once

#include <Shader.h>
#include <Util/BufferBuilder.h>

namespace Renderer {

class ColorRenderer {
public:
    void init();
    void windowSize(Vector2i size);
    void render(ColorBufferBuilder &buffer);
private:
    Shader shader_;
    GLuint aPosLocation_;
    GLuint aColorLocation_;
    GLuint uWindowSizeLocation_;
};

}
