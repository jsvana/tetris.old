#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "logging.h"
#include "screens/main_screen.h"
#include "screen.h"
#include "util.h"

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

GLFWwindow *window;

int screenWidth = 400;
int screenHeight = 400;

Color palette[PALETTE_COLOR_COUNT];

Screen *screen;

void glfwError(int err, const char *msg) {
	ERR("GLFW error %d:\n%s\n", err, msg);
}

void setColor(Color *color, GLfloat r, GLfloat g, GLfloat b) {
	color->r = r / 255.0f;
	color->g = g / 255.0f;
	color->b = b / 255.0f;
}

unsigned int getTime() {
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec * 1000000 + t.tv_usec;
}

void init() {
	int i, j;

	glewExperimental = GL_TRUE;
	glewInit();

	screen = new MainScreen();

	// Use 24-bit color for readability's sake
	float paletteColors[PALETTE_COLOR_COUNT][3] = {
		{118, 249, 251},
		{0, 72, 251},
		{243, 166, 51},
		{255, 248, 51},
		{168, 243, 19},
		{114, 44, 128},
		{233, 63, 51}
	};

	glClearColor(0.0, 0.0, 0.0, 1.0);

	for (i = 0; i < PALETTE_COLOR_COUNT; i++) {
		setColor(&(palette[i]), paletteColors[i][0],
			paletteColors[i][1], paletteColors[i][2]);
	}
}

void cleanup() {
	delete screen;
}

void key(GLFWwindow *window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

int main(int argc, char** argv) {
	if (!glfwInit()) {
		ERR("Failed to initialize GLFW\n");
		exit(1);
	}

	glfwSetErrorCallback(glfwError);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(screenWidth, screenHeight, "tetris", NULL, NULL);
	if (!window) {
		ERR("Error creating window\n");
		glfwTerminate();
		exit(1);
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key);

	init();

	unsigned int lastTime = getTime(), time;

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		time = getTime();
		screen->update(time - lastTime);
		lastTime = time;

		glClear(GL_COLOR_BUFFER_BIT);
		screen->render();
		glfwSwapBuffers(window);
	}

	cleanup();

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}
