#version 120

//varying vec2 TexCoord;
//varying vec3 Color;

//uniform sampler2D sampler;

void main() {
    //vec4 color = texture2D(sampler, TexCoord);

    //gl_FragColor = vec4(vec3(color.r) * Color, color.r);
    gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}