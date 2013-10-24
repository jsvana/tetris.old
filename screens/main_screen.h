#ifndef __MAIN_SCREEN_H
#define __MAIN_SCREEN_H

#include "../screen.h"

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
	glm::mat4 trans;

public:
	MainScreen();

	int update(unsigned int);
	void render();

	~MainScreen();
};

#endif
