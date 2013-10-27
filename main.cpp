#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "logging.h"

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "palette_manager.h"
#include "screen.h"
#include "screens/main_screen.h"
#include "util.h"

#include <vector>

GLFWwindow *window;

int screenWidth = 230;
int screenHeight = 420;

Screen *screen;

void glfwError(int err, const char *msg) {
	ERR("GLFW error %d:\n%s\n", err, msg);
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

	// Use 24-bit color for readability's sake
	std::vector<std::vector<float>> paletteColors = {
		{118, 249, 251},
		{0,   72,  251},
		{243, 166, 51},
		{255, 248, 51},
		{168, 243, 19},
		{114, 44,  128},
		{233, 63,  51}
	};

	glClearColor(0.0, 0.0, 0.0, 1.0);

	PaletteManager::getInstance()->setPalette(paletteColors);

	screen = new MainScreen();
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

	glm::mat4 proj = glm::ortho(0.0f, (float)screenWidth, (float)screenHeight,
		0.0f, -1.0f, 1.0f);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		time = getTime();
		screen->update(time - lastTime);
		lastTime = time;

		glClear(GL_COLOR_BUFFER_BIT);
		screen->render(proj);
		glfwSwapBuffers(window);
	}

	cleanup();

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}
