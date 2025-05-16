#pragma once

#include <vector>
#include <World/Platform.h>

namespace World {

class World {
public:
    World();
    void buildMesh(BufferBuilder &buffer_builder, Vector2i window_size) const;
private:
    std::vector<Platform> platforms_;
};

}
