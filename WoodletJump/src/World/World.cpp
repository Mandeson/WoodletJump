#include <World/World.h>

namespace World {

World::World() {
    platforms_.emplace(0.0f, Vector2f{0.0f, 0.6f});
}

void World::buildMesh(BufferBuilder &buffer_builder, Vector2i window_size) const {
    for (const auto &platform : platforms_)
        platform.second.buildMesh(buffer_builder, window_size);
}

}
