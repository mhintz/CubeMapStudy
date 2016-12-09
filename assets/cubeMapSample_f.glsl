#version 330

uniform samplerCube cubeMapTexture;

in vec3 TexCoord;
in vec4 Color;
in vec3 Normal;

out vec4 FragColor;

void main() {
  FragColor = texture(cubeMapTexture, TexCoord);
  // FragColor = vec4(1, 0, 0, 1);
}
