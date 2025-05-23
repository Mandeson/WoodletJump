#include <World/Platform.h>

namespace World {

Platform::Platform(Vector2f position, int segment_count) : position_(position), segments_{} {
    segments_.reserve(2 + 1);
    width_ = kPlatformEdgeSize.x + kPlatformMidSize * segment_count + kPlatformEdgeSize.x;
    position.x -= kPlatformEdgeSize.x;
    segments_.emplace_back(Box{{position.x, position.y - kPixelSize}, {kPlatformEdgeRenderSize.x, kPlatformEdgeRenderSize.y}}, kPlatformRightTextureRect);
    for (int i = 0; i < segment_count; i++) {
        position.x -= kPlatformMidSize;
        segments_.emplace_back(Box{{position.x, position.y - kPixelSize}, {kPlatformMidRenderSize.x, kPlatformMidRenderSize.y}}, kPlatformMidTextureRect);
    }
    segments_.emplace_back(Box{{position.x - kPlatformEdgeRenderSize.x, position.y - kPixelSize}, {kPlatformEdgeRenderSize.x, kPlatformEdgeRenderSize.y}}, kPlatformLeftTextureRect);
}

Vector2f Platform::getPosition() const {
    return position_;
}

float Platform::getWidth() const {
    return width_;
}

void Platform::buildMesh(BufferBuilder &buffer_builder, Vector2i window_size, const Camera &camera) const
{
    for (const auto &segment : segments_) {
        Box box = segment.getBox();
        float camera_position = static_cast<float>(camera.getPosition());
        Vector2f pixel_position = {(box.position.x - camera_position) * window_size.y, box.position.y * window_size.y};
        Vector2f pixel_size = {box.size.x * window_size.y, box.size.y * window_size.y};
        buffer_builder.addRectangle(pixel_position, pixel_size, segment.getTextureRect());
    }
}
}