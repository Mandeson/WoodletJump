#include <Renderer/SpriteRenderer.h>
#include <Sprite.h>

namespace Renderer {

void SpriteRenderer::init() {
    shader_.load("sprite");
    aPosLocation_ = shader_.getAttribLocation("aPos");
    aTexCoordLocation_ = shader_.getAttribLocation("aTexCoord");
    uTransformLocation_ = shader_.getUniformLocation("uTransform");
}

void SpriteRenderer::windowSize(Vector2i size) {
    projection_ = glm::ortho(0.0f, static_cast<float>(size.x), static_cast<float>(size.y), 0.0f);
}

/* Renders the sprite. Uses currently bound texture atlas. */
void SpriteRenderer::render(Sprite& sprite) {
    sprite.buffer_builder_.bind(aPosLocation_, aTexCoordLocation_);
    shader_.use();
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(sprite.position_.x, sprite.position_.y, 0.0f));
    model = glm::rotate(model, sprite.rotation_, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(sprite.size_.x, sprite.size_.y, 1.0f));
    Shader::setUniformMat4(uTransformLocation_, projection_ * model);
    glDrawElements(GL_TRIANGLES, sprite.buffer_builder_.getElementCount(), GL_UNSIGNED_INT, 0);
    Shader::reset();
    TextureBufferBuilder::reset(aPosLocation_, aTexCoordLocation_);
}

}
