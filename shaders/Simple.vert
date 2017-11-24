#version 330 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec4 vertexColor;
layout (location = 2) in vec2 vertexCoord;

out vec4 fragColor;
out vec2 fragCoord;

void main() {

  gl_Position = vec4(vertexPosition, 1.0f);
  fragColor   = vertexColor;
  fragCoord   = vec2(vertexCoord.x, vertexCoord.y);
}
