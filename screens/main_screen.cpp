#include "main_screen.h"

#include "../logging.h"
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
	/*
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cubes[i][j] = new Cube(-.875 + .25 * j, -.875 + .25 * i);
			cubes[i][j]->setSize(.125, .125);
			Color c(.125 * i, .125 * j, 0);
			cubes[i][j]->setColor(c);
		}
	}
	*/

	tetromino = new Tetromino(0, 0, I);
	tetrominoProj = glm::ortho(0, 200, 400, 0, -1, 1);
}

int MainScreen::update(unsigned int ticks) {
	return FALSE;
}

void MainScreen::render(glm::mat4 proj) {
	glViewport(0, 0, screenWidth, screenHeight);

	/*
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cubes[i][j]->render();
		}
	}
	*/

	glViewport(20, 10, screenWidth - 30, screenWidth - 20);
	tetromino->render(tetrominoProj);
}

MainScreen::~MainScreen() {
	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	glDeleteBuffers(1, &vbo);

	glDeleteVertexArrays(1, &vao);
}
