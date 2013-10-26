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
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cubes[i][j] = new Cube(.25 * j, .25 * i);
			cubes[i][j]->setSize(.125, .125);
			cubes[i][j]->setColor(.25 * i, .25 * j, 0);
		}
	}
}

int MainScreen::update(unsigned int ticks) {
	return FALSE;
}

void MainScreen::render() {
	glViewport(0, 0, screenWidth, screenHeight);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cubes[i][j]->render();
		}
	}
}

MainScreen::~MainScreen() {
	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	glDeleteBuffers(1, &vbo);

	glDeleteVertexArrays(1, &vao);
}
