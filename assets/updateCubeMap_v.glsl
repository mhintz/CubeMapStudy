#version 330

uniform mat4 ciModelViewProjection;
uniform mat3 ciNormalMatrix;

in vec4 ciPosition;

out highp vec3 TexCoord;

in vec4 ciColor;
out lowp vec4 Color;

in vec3 ciNormal;
out highp vec3 Normal;

void main() {
  gl_Position = ciModelViewProjection * ciPosition;
  TexCoord = ciPosition.xyz;
  Color = ciColor;
  Normal = ciNormalMatrix * ciNormal;
}
