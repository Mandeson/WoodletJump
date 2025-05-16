#pragma once

#include <Util/BufferBuilder.h>
#include <Constants.h>

namespace World {

class Platform {
public:
    Platform(Vector2f position);
    void buildMesh(BufferBuilder &buffer_builder, Vector2i window_size) const;
private:
    static constexpr TextureRect kPlatformLeftTextureRect = TextureRect(Constants::kTextureSize, {0, 81}, {127, 127});
    static constexpr TextureRect kPlatformMidTextureRect = TextureRect(Constants::kTextureSize, {128, 81}, {128, 130});
    Vector2f position_;
    //int segment_count_;
};

}
