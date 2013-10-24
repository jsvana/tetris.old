#version 410 core

uniform float t1Color;
uniform float t2Color;
uniform float t3Color;

in vec3 Color;
out vec4 outColor;

void main(void) {
	outColor = vec4(Color, 1.0);
}
