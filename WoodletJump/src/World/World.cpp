#include <World/World.h>

namespace World {

World::World() {
    platforms_.emplace(Platform::kPlatformEdgeWidth + Platform::kPlatformMidWidth, Vector2f{0.0f, 0.6f});
}

void World::buildMesh(BufferBuilder &buffer_builder, Vector2i window_size, const Camera &camera) const {
    float camera_pos = static_cast<float>(camera.getPosition());
    for (auto platform = platforms_.lower_bound(camera_pos); platform != platforms_.end(); platform++) {
        platform->second.buildMesh(buffer_builder, window_size);
    }
}

}
