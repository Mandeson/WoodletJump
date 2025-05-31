#include <Util/Color.h>

ColorF Color::normalize() {
    ColorF ret;
    ret.r = static_cast<float>(r) / 255;
    ret.g = static_cast<float>(g) / 255;
    ret.b = static_cast<float>(b) / 255;
    ret.a = static_cast<float>(a) / 255;
    return ret;
}
