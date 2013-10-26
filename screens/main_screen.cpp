#include "main_screen.h"

#include "../logging.h"
#include "../matrix.h"
#include "../shader_manager.h"
#include "../util.h"

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdlib.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <vector>

extern int screenWidth;
extern int screenHeight;

MainScreen::MainScreen() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLfloat vertices[] = {
		-0.5, 0.5,
		0.5, 0.5,
		0.5, -0.5,
		-0.5, -0.5
	};

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);

	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), elements,
		GL_STATIC_DRAW);

	std::vector<std::string> shaders = {
		"shaders/main.vert",
		"shaders/main.frag",
	};

	std::vector<GLuint> types = {
		GL_VERTEX_SHADER,
		GL_FRAGMENT_SHADER
	};

	for (int i = 0; i < shaders.size(); i++) {
		SHADERMAN->load(shaders[i], types[i]);
	}

	shaderProgram = SHADERMAN->buildProgram(shaders);

	glUseProgram(shaderProgram);

	posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

	uModel = glGetUniformLocation(shaderProgram, "model");
	model = glm::translate(model, glm::vec3(-.25, .25, 0));
	glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(model));

	uView = glGetUniformLocation(shaderProgram, "view");
	view = glm::lookAt(
		glm::vec3(0.0f, 1.2f, 1.2f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
	);
	glUniformMatrix4fv(uView, 1, GL_FALSE, glm::value_ptr(view));

	uProj = glGetUniformLocation(shaderProgram, "proj");
	proj = glm::perspective(45.0f, (float)screenWidth / screenHeight, 0.0f, 10.0f);
	glUniformMatrix4fv(uProj, 1, GL_FALSE, glm::value_ptr(proj));

	cube = new Cube(-1, -1);
	cube->setColor(1, 0, 1);
}

int MainScreen::update(unsigned int ticks) {
	return FALSE;
}

void MainScreen::render() {
	glViewport(0, 0, screenWidth, screenHeight);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glUseProgram(shaderProgram);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	cube->render();
}

MainScreen::~MainScreen() {
	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	glDeleteBuffers(1, &vbo);

	glDeleteVertexArrays(1, &vao);
}
