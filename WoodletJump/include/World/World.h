#pragma once

#include <map>
#include <World/Platform.h>
#include <Camera.h>

namespace World {

class World {
public:
    World();
    void buildMesh(BufferBuilder &buffer_builder, Vector2i window_size, const Camera &camera) const;
private:
    std::map<float, Platform> platforms_;
};

}
