#include "cube.h"

#include "../logging.h"
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

	uColor = glGetUniformLocation(shader, "color");

	uModel = glGetUniformLocation(shader, "model");
	uView = glGetUniformLocation(shader, "view");
	uProj = glGetUniformLocation(shader, "proj");

	size = glm::vec2(1, 1);
	setPosition(x, y);
}

void Cube::move(float x, float y) {
	position.x += x;
	position.y += y;

	glm::mat4 v;
	v = glm::translate(v, glm::vec3(position.x, position.y, 0));

	glUniformMatrix4fv(uView, 1, GL_FALSE, glm::value_ptr(v));
}

void Cube::setPosition(float x, float y) {
	position = glm::vec2(x, y);

	glm::mat4 v;
	v = glm::translate(v, glm::vec3(position.x, position.y, 0));

	glUniformMatrix4fv(uView, 1, GL_FALSE, glm::value_ptr(v));
}

void Cube::setColor(Color c) {
	glUniform3f(uColor, c.r, c.g, c.b);
}

void Cube::setSize(float w, float h) {
	size = glm::vec2(w, h);

	glm::mat4 s;
	s = glm::scale(s, glm::vec3(w, h, 1));

	glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(s));
}

void Cube::render(glm::mat4 proj) {
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glUseProgram(shader);

	glUniformMatrix4fv(uProj, 1, GL_FALSE, glm::value_ptr(proj));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Cube::~Cube() {
}
