#include "main_screen.h"

#include "../logging.h"
#include "../matrix.h"
#include "../shader.h"
#include "../util.h"

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdlib.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

extern int screenWidth;
extern int screenHeight;

MainScreen::MainScreen() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLfloat vertices[] = {
		-0.5, 0.5, 1, 0, 0,
		0.5, 0.5, 0, 1, 0,
		0.5, -0.5, 0, 0, 1,
		-0.5, -0.5, 1, 1, 0
	};

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 20 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);

	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), elements,
		GL_STATIC_DRAW);

	char *shaderSource = shaderRead("vertex.vert");
	const char *source = shaderSource;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &source, NULL);
	free(shaderSource);

	glCompileShader(vertexShader);

	if (!shaderDidCompile(vertexShader)) {
		shaderPrintCompileLog(vertexShader);
	}

	shaderSource = shaderRead("fragment.frag");
	source = shaderSource;

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &source, NULL);
	free(shaderSource);

	glCompileShader(fragmentShader);

	if (!shaderDidCompile(fragmentShader)) {
		shaderPrintCompileLog(fragmentShader);
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

	colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
		(void *)(2 * sizeof(float)));

	transUniform = glGetUniformLocation(shaderProgram, "trans");
	trans = glm::translate(trans, glm::vec3(0, 0, 0));
	glUniformMatrix4fv(transUniform, 1, GL_FALSE, glm::value_ptr(trans));
}

int MainScreen::update(unsigned int ticks) {
	return FALSE;
}

void MainScreen::render() {
	//glViewport(0, 0, screenWidth / 2, screenHeight / 2);

	//glUniformMatrix4fv(transUniform, 1, GL_FALSE, glm::value_ptr(trans));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

MainScreen::~MainScreen() {
	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	glDeleteBuffers(1, &vbo);

	glDeleteVertexArrays(1, &vao);
}
