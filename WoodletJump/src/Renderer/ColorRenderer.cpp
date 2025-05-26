#include <Renderer/ColorRenderer.h>

namespace Renderer {

void ColorRenderer::init() {
    shader_.load("color");
    aPosLocation_ = shader_.getAttribLocation("aPos");
    aColorLocation_ = shader_.getAttribLocation("aColor");
    uWindowSizeLocation_ = shader_.getUniformLocation("uWindowSize");
}

void ColorRenderer::windowSize(Vector2i size) {
    shader_.use();
    Shader::setUniform2f(uWindowSizeLocation_, {static_cast<float>(size.x),
        static_cast<float>(size.y)});
    Shader::reset();
}

void ColorRenderer::render(ColorBufferBuilder &buffer) {
    buffer.bind(aPosLocation_, aColorLocation_);
    shader_.use();
    glDrawElements(GL_TRIANGLES, buffer.getElementCount(), GL_UNSIGNED_INT, 0);
    Shader::reset();
    TextureBufferBuilder::reset(aPosLocation_, aColorLocation_);
}

}
