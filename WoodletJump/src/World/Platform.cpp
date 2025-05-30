#include <World/Platform.h>

namespace World {

Platform::Platform(Vector2d position, int segment_count) : position_(position), segments_{} {
    segments_.reserve(2 + 1);
    width_ = kPlatformEdgeSize.x + kPlatformMidSize * segment_count + kPlatformEdgeSize.x;
    position.x -= kPlatformEdgeSize.x;
    segments_.emplace_back(BoxDF{{position.x, position.y - kPixelSize}, {kPlatformEdgeRenderSize.x, kPlatformEdgeRenderSize.y}}, kPlatformRightTextureRect);
    for (int i = 0; i < segment_count; i++) {
        position.x -= kPlatformMidSize;
        segments_.emplace_back(BoxDF{{position.x, position.y - kPixelSize}, {kPlatformMidRenderSize.x, kPlatformMidRenderSize.y}}, kPlatformMidTextureRect);
    }
    segments_.emplace_back(BoxDF{{position.x - kPlatformEdgeRenderSize.x, position.y - kPixelSize}, {kPlatformEdgeRenderSize.x, kPlatformEdgeRenderSize.y}}, kPlatformLeftTextureRect);
}

Vector2d Platform::getPosition() const {
    return position_;
}

float Platform::getWidth() const {
    return width_;
}

void Platform::buildMesh(TextureBufferBuilder &buffer_builder, Vector2i window_size, const Camera &camera) const
{
    for (const auto &segment : segments_) {
        BoxDF box = segment.getBox();
        double camera_position = camera.getPosition();
        Vector2f pixel_position = {static_cast<float>((box.position.x - camera_position) * window_size.y), static_cast<float>(box.position.y) * window_size.y};
        Vector2f pixel_size = {box.size.x * window_size.y, box.size.y * window_size.y};
        buffer_builder.addRectangle(pixel_position, pixel_size, segment.getTextureRect());
    }
}
}