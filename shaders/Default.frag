#version 330 core

in vec4 fragmentColor;
in vec2 fragmentCoord;

out vec4 color;

uniform sampler2D sampler;

void main() {

  color = texture(sampler, fragmentCoord) * fragmentColor;
}
