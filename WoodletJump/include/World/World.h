#pragma once

#include <map>
#include <functional>
#include <World/Platform.h>
#include <Camera.h>

namespace World {

class World {
public:
    World();
    void buildMesh(BufferBuilder &buffer_builder, Vector2i window_size, const Camera &camera) const;
    bool checkCollision(const Camera &camera, Box object) const;
    // Checks if the given object collides with any platform that is below it
    bool checkCollisionBelow(const Camera &camera, Box object) const;
private:
    // Executes lambda for every platform within the given camera view, as long as lambda returns true. If lambda returns false, forEachVisiblePlatform returns.
    void forEachVisiblePlatform(const Camera &camera, std::function<bool(const Platform &)> lambda) const;
    std::map<float, Platform> platforms_;
};

}
