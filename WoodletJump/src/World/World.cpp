#include <World/World.h>

namespace World {

World::World() {
    float position = Platform::kPlatformEdgeSize.x + Platform::kPlatformMidSize + Platform::kPlatformEdgeSize.x;
    platforms_.emplace(position, Vector2f{position, 0.6f});
}

void World::buildMesh(BufferBuilder &buffer_builder, Vector2i window_size, const Camera &camera) const {
    forEachVisiblePlatform(camera, [&buffer_builder, window_size](const Platform &platform) {
        platform.buildMesh(buffer_builder, window_size);
        return true; // continue the loop
    });
}

bool World::checkCollision(const Camera &camera, Box object) const {
    bool colision = false;
    forEachVisiblePlatform(camera, [&object, &colision](const Platform &platform) {
        Vector2f position = platform.getPosition();
        Vector2f size = {platform.getWidth(), Platform::kPlatformMidSize};
        position.x -= size.x;
        if ((object.position.x + object.size.x > position.x && object.position.x < position.x + size.x)
                && (object.position.y + object.size.y > position.y && object.position.y < position.y + size.y)) {
            colision = true;
            return false; // do not continue the loop
        } else {
            return true; // continue the loop
        }
    });
    return colision;
}

void World::forEachVisiblePlatform(const Camera &camera, std::function<bool(const Platform &)> lambda) const {
    float camera_pos = static_cast<float>(camera.getPosition());
    float camera_bound = camera_pos + camera.getWidth();
    for (auto element = platforms_.lower_bound(camera_pos); element != platforms_.end(); element++) {
        if (element->first - Platform::kPlatformMaxWidth > camera_bound) // next elements surely are outside the camera view
            break;
        
        const auto &platform = element->second;
        if (element->first - platform.getWidth() <= camera_bound) // inside the camera view
            if (!lambda(platform))
                break;
    }
}
}
