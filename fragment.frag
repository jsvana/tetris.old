#version 410 core

uniform vec3 triangleColor;

out vec4 outColor;

void main(void) {
	outColor = vec4(triangleColor, 1.0);
}
