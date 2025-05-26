#version 120

attribute vec2 aPos;
attribute vec4 aColor;

uniform vec2 uWindowSize;

varying vec4 Color;

void main() {
    gl_Position = vec4(aPos.x / uWindowSize.x * 2.0f - 1.0f,
            aPos.y / uWindowSize.y * -2.0f + 1.0f, 0.0f, 1.0f);

    Color = aColor;
}
