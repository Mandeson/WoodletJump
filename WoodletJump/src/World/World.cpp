#include <World/World.h>
#include <Logger.h>

namespace World {

World::World() {
    float position = Platform::kPlatformEdgeSize.x + Platform::kPlatformMidSize + Platform::kPlatformEdgeSize.x;
    platforms_.emplace(position, Platform{Vector2f{position, 0.6f}, 1});
    generated_ = position - kNextPlatformMinXDistance;
}

void World::World::generate(std::mt19937 &random, const Camera &camera) {
    float limit = static_cast<float>(camera.getPosition()) + camera.getWidth();
    while (generated_ < limit + Platform::kPlatformMaxWidth) {
        const auto &last_platform = std::prev(platforms_.end())->second;
        float platform_pos_y_min = last_platform.getPosition().y - kNextPlatformMaxYDistance;
        float platform_pos_y_max = platform_pos_y_min + kNextPlatformMaxYDistance * 2;
        if (platform_pos_y_min < kPlatformBoundUp) {
            float diff = kPlatformBoundUp - platform_pos_y_min;
            platform_pos_y_min += diff;
            platform_pos_y_max += diff;
        } else if (platform_pos_y_max + Platform::kPlatformMidSize > kPlatformBoundDown) {
            float diff = platform_pos_y_max + Platform::kPlatformMidSize - kPlatformBoundDown;
            platform_pos_y_min -= diff;
            platform_pos_y_max -= diff;
        }
        std::uniform_real_distribution<float> platform_pos_y{platform_pos_y_min, platform_pos_y_max};
        std::uniform_real_distribution<float> distance{kNextPlatformMinXDistance, kNextPlatformMaxXDistance};
        std::uniform_int_distribution<int> segment_count_dist{0, Platform::kMaxPlatformCount};
        int segment_count = segment_count_dist(random);

        float position = distance(random) + generated_ + Platform::kPlatformEdgeSize.x + Platform::kPlatformMidSize * segment_count
                 + Platform::kPlatformEdgeSize.x;
        platforms_.emplace(position, Platform{Vector2f{position, platform_pos_y(random)}, segment_count});
        generated_ = std::max(generated_, position);
    }
}

void World::buildMesh(BufferBuilder &buffer_builder, Vector2i window_size, const Camera &camera) const {
    forEachVisiblePlatform(camera, [&buffer_builder, window_size, &camera](const Platform &platform) {
        platform.buildMesh(buffer_builder, window_size, camera);
        return true; // continue the loop
    });
}

bool World::checkCollision(const Camera &camera, Box object) const {
    bool colision = false;
    forEachVisiblePlatform(camera, [&object, &colision](const Platform &platform) {
        Vector2f position = platform.getPosition();
        Vector2f size = {platform.getWidth(), Platform::kPlatformMidSize};
        position.x -= size.x;
        if (object.position.x + object.size.x > position.x && object.position.x < position.x + size.x
                && object.position.y + object.size.y > position.y && object.position.y < position.y + size.y) {
            colision = true;
            return false; // do not continue the loop
        } else {
            return true; // continue the loop
        }
    });
    return colision;
}

bool World::checkCollisionBelow(const Camera &camera, Box object) const {
    bool colision = false;
    forEachVisiblePlatform(camera, [&object, &colision](const Platform &platform) {
        Vector2f position = platform.getPosition();
        Vector2f size = {platform.getWidth(), Platform::kPlatformMidSize};
        position.x -= size.x;
        if (object.position.x + object.size.x > position.x && object.position.x < position.x + size.x
                && object.position.y + object.size.y > position.y && object.position.y + object.size.y <= position.y + size.y) {
            colision = true;
            return false; // do not continue the loop
        } else {
            return true; // continue the loop
        }
    });
    return colision;
}

bool World::checkCollisionAbove(const Camera &camera, Box object) const {
    bool colision = false;
    forEachVisiblePlatform(camera, [&object, &colision](const Platform &platform) {
        Vector2f position = platform.getPosition();
        Vector2f size = {platform.getWidth(), Platform::kPlatformMidSize};
        position.x -= size.x;
        if (object.position.x + object.size.x > position.x && object.position.x < position.x + size.x
                && object.position.y >= position.y && object.position.y < position.y + size.y) {
            colision = true;
            return false; // do not continue the loop
        } else {
            return true; // continue the loop
        }
    });
    return colision;
}

void World::forEachVisiblePlatform(const Camera &camera, std::function<bool(const Platform &)> lambda) const
{
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
