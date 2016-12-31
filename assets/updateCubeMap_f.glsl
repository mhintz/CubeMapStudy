#version 410

in vec4 aColor;

out vec4 FragColor;

void main() {
  // For seeing the default frag coordinate orientation for the cubemap:
  // FragColor = vec4(gl_FragCoord.xy / 600, 0, 1);
  FragColor = aColor;
}
