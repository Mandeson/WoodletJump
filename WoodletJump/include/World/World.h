#pragma once

#include <map>
#include <functional>
#include <World/Platform.h>
#include <Camera.h>
#include <random>

namespace World {

class World {
public:
    World();
    void generate(std::mt19937 &random, const Camera &camera);
    void buildMesh(BufferBuilder &buffer_builder, Vector2i window_size, const Camera &camera) const;
    bool checkCollision(const Camera &camera, Box object) const;
    // Checks if the given object collides with any platform that is below it
    bool checkCollisionBelow(const Camera &camera, Box object) const;
    // Checks if the given object collides with any platform that is above it
    bool checkCollisionAbove(const Camera &camera, Box object) const;
private:
    // Executes lambda for every platform within the given camera view, as long as lambda returns true. If lambda returns false, forEachVisiblePlatform returns.
    void forEachVisiblePlatform(const Camera &camera, std::function<bool(const Platform &)> lambda) const;

    std::map<float, Platform> platforms_;
    float generated_;
};

}
