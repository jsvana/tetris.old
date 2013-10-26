#include "cube.h"

#include "../shader_manager.h"

#include <string>
#include <vector>

Cube::Cube(float x, float y) {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLfloat verts[] = {
		-1,  1,
		 1,  1,
		 1, -1,
		-1, -1
	};

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), verts, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);

	GLuint els[] = {
		0, 1, 2,
		2, 3, 0
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), els,
		GL_STATIC_DRAW);

	std::vector<std::string> shaders = {
		"shaders/cube.vert",
		"shaders/cube.frag",
	};

	std::vector<int> types = {
		GL_VERTEX_SHADER,
		GL_FRAGMENT_SHADER
	};

	for (int i = 0; i < shaders.size(); i++) {
		SHADERMAN->load(shaders[i], types[i]);
	}

	shader = SHADERMAN->buildProgram(shaders);
	glUseProgram(shader);

	posAttrib = glGetAttribLocation(shader, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

	size = glm::vec3(1, 1, 1);
}

void Cube::move(float x, float y) {
}

void Cube::render() {
	glViewport(0, 0, 10, 10);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glUseProgram(shader);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Cube::~Cube() {
}
