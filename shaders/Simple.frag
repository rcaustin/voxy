#version 330 core

in vec4 fragColor;
in vec2 fragCoord;

out vec4 color;

uniform sampler2D sampler;

void main() {

  color = texture(sampler, fragCoord) * fragColor;
}
