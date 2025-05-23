#include <Camera.h>

void Camera::windowSize(Vector2i window_size) {
    width_ = static_cast<float>(window_size.x) / window_size.y;
}

void Camera::setPosition(double position) {
    posisiton_ = position;
}

double Camera::getPosition() const {
    return posisiton_;
}

float Camera::getWidth() const {
    return width_;
}
