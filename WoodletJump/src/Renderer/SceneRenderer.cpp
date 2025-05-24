#include <Renderer/SceneRenderer.h>

namespace Renderer {

void SceneRenderer::init() {
    shader_.load("scene");
    aPosLocation_ = shader_.getAttribLocation("aPos");
    aTexCoordLocation_ = shader_.getAttribLocation("aTexCoord");
    uWindowSizeLocation_ = shader_.getUniformLocation("uWindowSize");
}

void SceneRenderer::windowSize(Vector2i size) {
    shader_.use();
    shader_.setUniform2f(uWindowSizeLocation_, {static_cast<float>(size.x),
            static_cast<float>(size.y)});
    Shader::reset();
}

BufferBuilder& SceneRenderer::getBufferBuilder() {
    return buffer_builder_;
}

void SceneRenderer::render() {
    buffer_builder_.upload(GL_STREAM_DRAW);
    buffer_builder_.bind(aPosLocation_, aTexCoordLocation_);
    shader_.use();
    glDrawElements(GL_TRIANGLES, buffer_builder_.getElementCount(), GL_UNSIGNED_INT, 0);
    Shader::reset();
    BufferBuilder::reset(aPosLocation_, aTexCoordLocation_);
}

}
