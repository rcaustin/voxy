#version 330 core

in vec3 vertexPosition;
in vec4 vertexColor;
in vec2 vertexCoord;

out vec4 fragmentColor;
out vec2 fragmentCoord;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {

  gl_Position = projectionMatrix * viewMatrix * vec4(vertexPosition, 1.0f);
  fragmentColor = vertexColor;
  fragmentCoord = vec2(vertexCoord.x, 1.0f - vertexCoord.y);
}
