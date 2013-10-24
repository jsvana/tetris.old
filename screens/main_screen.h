#ifndef __MAIN_SCREEN_H
#define __MAIN_SCREEN_H

#include "../screen.h"

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class MainScreen : public Screen {
private:
	GLuint vao, vbo;
	GLuint vertexShader, fragmentShader;
	GLuint shaderProgram;
	GLuint uniColor, transUniform;
	GLuint posAttrib;

	GLfloat vertices[6] = {
		0, 0.5,
		0.5, -0.5,
		-0.5, -0.5
	};

public:
	MainScreen();

	int update(unsigned int);
	void render();

	~MainScreen();
};

#endif
