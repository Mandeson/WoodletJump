#include <World/Platform.h>

namespace World {

Platform::Platform(Vector2f position) : position_(position) { }

void Platform::buildMesh(BufferBuilder &buffer_builder, Vector2i window_size) const {
    Vector2f pixel_position = {position_.x * window_size.y, position_.y * window_size.y};
    float pixel_size = 0.07f * window_size.y;
    buffer_builder.addRectangle(pixel_position, {pixel_size, pixel_size}, kPlatformLeftTextureRect);
}

}