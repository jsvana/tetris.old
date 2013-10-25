#ifndef __MAIN_SCREEN_H
#define __MAIN_SCREEN_H

#include "../screen.h"

#include "../objs/cube.h"

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

class MainScreen : public Screen {
private:
	GLuint vao, vbo, ebo;
	GLuint vertexShader, fragmentShader;
	GLuint shaderProgram;
	GLuint uniColor1, uniColor2, uniColor3, transUniform;
	GLuint posAttrib, colAttrib;
	GLuint uProj, uView, uModel;
	glm::mat4 proj, view, model;

	Cube *cube;

public:
	MainScreen();

	int update(unsigned int ticks);
	void render();

	~MainScreen();
};

#endif
