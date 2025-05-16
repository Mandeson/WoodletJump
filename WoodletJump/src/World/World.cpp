#include <World/World.h>

namespace World {

World::World() {
    platforms_.emplace_back(Vector2f{0.5f, 0.5f});
}

void World::buildMesh(BufferBuilder &buffer_builder, Vector2i window_size) const {
    for (const auto &platform : platforms_)
        platform.buildMesh(buffer_builder, window_size);
}

}
