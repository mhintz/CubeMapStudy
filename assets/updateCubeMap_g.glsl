#version 410

layout (points, invocations = 6) in;
layout (triangle_strip, max_vertices = 4) out;

out vec4 aColor;

vec4[4] rectCorners = vec4[](
  vec4(-1, 1, 0, 1),
  vec4(-1, -1, 0, 1),
  vec4(1, 1, 0, 1),
  vec4(1, -1, 0, 1)
);

#define NUM_SIDES 6

vec4[NUM_SIDES] faceColors = vec4[](
  vec4(1, 0, 0, 1),
  vec4(0, 1, 1, 1),
  vec4(0, 1, 0, 1),
  vec4(1, 0, 1, 1),
  vec4(0, 0, 1, 1),
  vec4(1, 1, 0, 1)
);

void main() {
  gl_Layer = gl_InvocationID;

  for (int i = 0; i < 4; i++) {
    aColor = faceColors[gl_InvocationID];
    gl_Position = rectCorners[i];
    EmitVertex();
  }

  EndPrimitive();
}
