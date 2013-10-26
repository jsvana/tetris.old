#ifndef __UTIL_H
#define __UTIL_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define PALETTE_COLOR_COUNT 7

#define TILE_WIDTH 20
#define TILE_HEIGHT 20

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#define RIGHT 3
#define UP 2
#define LEFT 1
#define DOWN 0

class Color {
public:
  GLfloat r, g, b;

	Color(float red, float green, float blue) {
		r = red / 255.0f;
		g = green / 255.0f;
		b = blue / 255.0f;
	}
};

#endif
