#include <cmath>
#include <Util/Vector.h>

Vector2d Vector2d::normalize() {
    double root = sqrt(x * x + y * y);
    return {x / root, y / root};
}
Vector2f Vector2i::toFloat() {
    return {static_cast<float>(x), static_cast<float>(y)};
}
