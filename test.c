#include <GLFW/glfw3.h>
#include <stdlib.h>

int screenWidth = 400;
int screenHeight = 400;

GLuint vbo;

GLfloat vertices[] = {
	0, .75, 0, // 0 bottom front left
	0, 0, 0, // 1 top front left
	.75, .75, 0, // 2 bottom front right
	.75, 0, 0, // 3 top front right
};

GLuint indices[] = {
	0, 1, 3, // left bottom triangle
	0, 2, 3, // left top triangle
};

void render() {
	glEnableClientState(GL_VERTEX_ARRAY);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);

	glDisableClientState(GL_VERTEX_ARRAY);
}

int main(int argc, char **argv) {
	if (!glfwInit()) {
		exit(1);
	}

	GLFWwindow *window = glfwCreateWindow(screenWidth, screenHeight, "tetris", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(1);
	}

	glfwMakeContextCurrent(window);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	glVertexPointer(3, GL_FLOAT, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		render();

		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}
