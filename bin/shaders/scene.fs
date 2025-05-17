#version 120

varying vec2 TexCoord;

uniform sampler2D sampler;

void main() {
    vec4 color = texture2D(sampler, TexCoord);

    gl_FragColor = vec4(color);
}