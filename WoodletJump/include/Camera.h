#pragma once

#include <Util/Vector.h>

class Camera {
public:
    void windowSize(Vector2i window_size);
    void setPosition(float position);
    float getPosition() const;
    float getWidth() const;
private:
    float posisiton_{};
    float width_{};
};
