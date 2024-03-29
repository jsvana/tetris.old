#ifndef __MAIN_SCREEN_H
#define __MAIN_SCREEN_H

#include "../screen.h"

#include "../objs/cube.h"
#include "../objs/tetromino.h"

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <vector>

class MainScreen : public Screen {
private:
	GLuint vao, vbo, ebo;
	GLuint vertexShader, fragmentShader;
	GLuint shaderProgram;
	GLuint uniColor1, uniColor2, uniColor3, transUniform;
	GLuint posAttrib, colAttrib;
	GLuint uView, uModel;
	glm::mat4 view, model;
	glm::mat4 tetrominoProj;

	Cube *cubes[8][8];
	Tetromino *tetromino;

public:
	MainScreen();

	int update(unsigned int ticks);
	void render(glm::mat4 proj);

	~MainScreen();
};

#endif
