#ifndef __CUBE_H
#define __CUBE_H

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Cube {
private:
	GLuint vao, vbo, ebo;
	GLuint shader;
	GLuint posAttrib;
	GLuint uColor;
	glm::mat4 trans = glm::mat4();
	glm::vec3 size;
	glm::vec3 color;

public:
	Cube(float x, float y);

	void move(float x, float y);
	void setColor(float r, float g, float b);
	void render();

	~Cube();
};

#endif
