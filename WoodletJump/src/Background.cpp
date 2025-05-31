#include <Background.h>

void Background::render(Renderer::ColorRenderer &renderer, Vector2i window_size) {
    buffer_builder_.clear();
    buffer_builder_.addGradient({0.0f, 0.0f}, window_size.toFloat(), kColorTop, kColorBottom);
    buffer_builder_.upload(GL_STREAM_DRAW);
    renderer.render(buffer_builder_);
}
