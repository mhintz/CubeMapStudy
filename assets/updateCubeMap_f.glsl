#version 330

uniform int cubeSide;

in vec3 TexCoord;
in vec4 Color;
in vec3 Normal;

out vec4 FragColor;

#define NUM_SIDES 6

vec4[NUM_SIDES] colors = vec4[](
  vec4(1, 0, 0, 1),
  vec4(0, 1, 0, 1),
  vec4(0, 0, 1, 1),
  vec4(1, 1, 0, 1),
  vec4(1, 0, 1, 1),
  vec4(0, 1, 1, 1)
);

void main() {
  FragColor = colors[cubeSide];
}
