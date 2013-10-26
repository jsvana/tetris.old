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
	GLuint uModel, uView;
	glm::vec2 position;
	glm::vec2 size;
	glm::vec3 color;

public:
	Cube(float x, float y);

	void move(float x, float y);
	void setPosition(float x, float y);
	void setSize(float w, float h);
	void setColor(float r, float g, float b);

	void render();

	~Cube();
};

#endif
