#version 410 core

in vec2 position;

uniform mat4 view;
uniform mat4 model;

void main() {
	gl_Position = view * model * vec4(position, 0.0, 1.0);
}
