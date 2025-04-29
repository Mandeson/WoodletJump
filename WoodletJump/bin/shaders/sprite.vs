#version 120

attribute vec2 aPos;
attribute vec2 aTexCoord;

uniform mat4 uTransform;

varying vec2 TexCoord;

void main() {
    gl_Position = uTransform * vec4(aPos.x, aPos.y, 0.0f, 1.0f);

    TexCoord = aTexCoord;
}
