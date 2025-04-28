#version 120

attribute vec2 aPos;
//attribute vec2 aTexCoord;

//varying vec2 TexCoord;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, 0.0f, 1.0f);

    //TexCoord = aTexCoord;
}
