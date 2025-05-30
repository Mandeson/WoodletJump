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
    void reset();
    void generate(std::mt19937 &random, const Camera &camera);
    void buildMesh(TextureBufferBuilder &buffer_builder, Vector2i window_size, const Camera &camera) const;
    bool checkCollision(const Camera &camera, Box object) const;
    // Checks if the given object collides with any platform that is below it
    bool checkCollisionBelow(const Camera &camera, Box object) const;
    // Checks if the given object collides with any platform that is above it
    bool checkCollisionAbove(const Camera &camera, Box object) const;
private:
    static constexpr float kNextPlatformMinXDistance = -0.15f;
    static constexpr float kNextPlatformMaxXDistance = 0.25f;
    static constexpr float kNextPlatformMaxYDistance = 0.15f;
    static constexpr float kPlatformBoundUp = 0.2f;
    static constexpr float kPlatformBoundDown = 1.0f - Platform::kPlatformMidSize;

    // Executes lambda for every platform within the given camera view, as long as lambda returns true. If lambda returns false, forEachVisiblePlatform returns.
    void forEachVisiblePlatform(const Camera &camera, std::function<bool(const Platform &)> lambda) const;

    std::map<double, Platform> platforms_;
    double generated_;
};

}
