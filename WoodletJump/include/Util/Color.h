#pragma once

#include <cstdint>

struct ColorF
{
    float r;
    float g;
    float b;
    float a;
};

struct Color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
    ColorF normalize();
};
