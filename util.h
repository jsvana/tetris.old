#ifndef __UTIL_H
#define __UTIL_H

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

typedef struct {
  GLfloat r, g, b;
} Color;

#endif
