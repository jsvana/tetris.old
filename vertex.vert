#version 410 core

in vec2 position;
in vec3 color;

out vec3 Color;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main() {
	Color = color;
	gl_Position = proj * view * model * vec4(position, 0.0, 1.0);
}
