#pragma once

#include <Util/Vector.h>

class Camera {
public:
    void reset();
    void windowSize(Vector2i window_size);
    void setPosition(double position);
    double getPosition() const;
    float getWidth() const;
private:
    double posisiton_{};
    float width_{};
};
