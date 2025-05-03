#pragma once

#include <Shader.h>
#include <Util/Vector.h>

class Sprite;

namespace Renderer {

class SpriteRenderer {
public:
    void init();
    void windowSize(Vector2i size);
    void render(Sprite& sprite);
private:
    Shader shader_;
    GLuint aPosLocation_;
    GLuint aTexCoordLocation_;
    GLuint uTransformLocation_;
    glm::mat4 projection_;
};

}
