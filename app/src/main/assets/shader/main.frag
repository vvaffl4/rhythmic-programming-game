#version 310 es
precision mediump float;

in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D image;
uniform vec4 color;

void main() {
    vec4 textureColor = texture(image, TexCoords);
    if(textureColor.a < 0.1f)
        discard;

    FragColor = color * textureColor;
}