#include "main_screen.h"

#include "../logging.h"
#include "../matrix.h"
#include "../shader.h"
#include "../util.h"

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gsl/gsl_matrix.h>
#include <math.h>
#include <stdlib.h>

extern int screenWidth;
extern int screenHeight;

GLuint vao, vbo;
GLuint vertexShader, fragmentShader;
GLuint shaderProgram;
GLuint uniColor, transUniform;
GLuint posAttrib;

GLfloat vertices[] = {
	0, 0.5,
	0.5, -0.5,
	-0.5, -0.5
};

int mainScreenUpdate(Screen *s, unsigned int ticks) {
	static unsigned int clock = 0;
	clock += ticks / 100;
	glUniform3f(uniColor, (sin(clock / 5000.0f) + 1.0f) / 2.0f, 0.0f, 0.0f);
	return FALSE;
}

void mainScreenRender(Screen *s) {
	//glViewport(0, 0, screenWidth / 2, screenHeight / 2);

	Matrix *m = scaleMatrix4(1.25, 1, 1);

	transUniform = glGetUniformLocation(shaderProgram, "trans");
	glUniformMatrix4fv(transUniform, 1, GL_TRUE, (float *)m->data);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

Screen *mainScreenCreate() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

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
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

	uniColor = glGetUniformLocation(shaderProgram, "triangleColor");

	Screen *s = malloc(sizeof(Screen));

	if (s == NULL) {
		ERR("Error allocating memory\n");
		exit(1);
	}

	s->data = malloc(sizeof(MainScreenData));

	if (s->data == NULL) {
		ERR("Error allocating memory\n");
		exit(1);
	}

	s->type = MAIN_SCREEN;
	s->update = mainScreenUpdate;
	s->render = mainScreenRender;

	Matrix *sc = scaleMatrix4(2, 3, 4);
	Matrix *r = rotationMatrix4(90, 0, 0, 1);
	matrixPrint(sc);
	printf("\n");
	matrixPrint(r);
	printf("\n");

	Matrix *out = matrixMultiply(sc, r);
	matrixPrint(out);
	printf("\n");

	Matrix *t = matrixTranspose(out);
	matrixPrint(t);

	matrixDestroy(sc);
	matrixDestroy(r);
	matrixDestroy(out);
	matrixDestroy(t);

	return s;
}

void mainScreenDestroy(Screen *s) {
	if (s == NULL) {
		return;
	}

	free(s->data);
	free(s);

	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	glDeleteBuffers(1, &vbo);

	glDeleteVertexArrays(1, &vao);
}
