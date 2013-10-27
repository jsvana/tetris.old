#pragma once

#ifndef __TETROMINO_H
#define __TETROMINO_H

#include "Cube.h"

#include <glm/glm.hpp>
#include <vector>

enum TetrominoType {
	I,
	J,
	L,
	O,
	S,
	T,
	Z
};

class Tetromino {
private:
	int type;
	std::vector<Cube> cubes;
	glm::vec2 position;

public:
	Tetromino(float x, float y, int type);

	void setPosition(float x, float y);

	void render(glm::mat4 proj);

	~Tetromino();
};

#endif
