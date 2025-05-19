#pragma once

struct Vector2f {
    float x;
    float y;
};

struct Vector2d {
    double x;
    double y;
    Vector2d normalize();
};

struct Vector2i {
    int x;
    int y;
};
