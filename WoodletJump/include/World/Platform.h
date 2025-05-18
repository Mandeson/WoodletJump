#pragma once

#include <vector>
#include <Util/BufferBuilder.h>
#include <Util/Segment.h>
#include <Constants.h>

namespace World {

class Platform {
public:
    Platform(Vector2f position);
    Vector2f getPosition() const;
    float getWidth() const;
    void buildMesh(BufferBuilder &buffer_builder, Vector2i window_size) const;

    static constexpr int kPlatformMidPixelSize = 128;
    static constexpr float kPlatformMidSize = 0.07f;
    static constexpr Vector2i kPlatformEdgePixelSize = {126, 125};
    static constexpr Vector2f kPlatformEdgeSize = {
            static_cast<float>(kPlatformEdgePixelSize.x) / kPlatformMidPixelSize * kPlatformMidSize,
            static_cast<float>(kPlatformEdgePixelSize.y) / kPlatformMidPixelSize * kPlatformMidSize
    };
    static constexpr float kPlatformMaxWidth = 2 * kPlatformEdgeSize.x + 5 * kPlatformMidSize;
private:
    static constexpr TextureRect kPlatformLeftTextureRect = TextureRect(Constants::kTextureSize, {0, 81}, {127, 127});
    static constexpr TextureRect kPlatformMidTextureRect = TextureRect(Constants::kTextureSize, {127, 81}, {128, 130});
    static constexpr TextureRect kPlatformRightTextureRect = TextureRect(Constants::kTextureSize, {255, 81}, {127, 127});
    static constexpr float kPixelSize = kPlatformMidSize / kPlatformMidPixelSize;
    static constexpr Vector2f kPlatformMidRenderSize = {kPlatformMidSize,
            static_cast<float>(kPlatformMidPixelSize + 2) / kPlatformMidPixelSize * kPlatformMidSize};
    static constexpr Vector2f kPlatformEdgeRenderSize = {
            static_cast<float>(kPlatformEdgePixelSize.x + 1) / kPlatformMidPixelSize * kPlatformMidSize,
            static_cast<float>(kPlatformEdgePixelSize.y + 2) / kPlatformMidPixelSize * kPlatformMidSize
    };
    
    float width_;
    Vector2f position_;
    std::vector<Segment> segments_;
};

}
