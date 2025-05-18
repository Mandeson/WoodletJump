#include <World/World.h>

namespace World {

World::World() {
    float position = Platform::kPlatformEdgeSize.x + Platform::kPlatformMidSize + Platform::kPlatformEdgeSize.x;
    platforms_.emplace(position, Vector2f{position, 0.6f});
}

void World::buildMesh(BufferBuilder &buffer_builder, Vector2i window_size, const Camera &camera) const {
    float camera_pos = static_cast<float>(camera.getPosition());
    float camera_bound = camera_pos + camera.getWidth();
    for (auto element = platforms_.lower_bound(camera_pos); element != platforms_.end(); element++) {
        if (element->first - Platform::kPlatformMaxWidth > camera_bound) // next elements surely are outside the camera view
            break;
        
        const auto &platform = element->second;
        if (element->first - platform.getWidth() <= camera_bound) // do not draw if outside the screen
            platform.buildMesh(buffer_builder, window_size);
    }
}

}
