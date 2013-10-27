#include "tetromino.h"

#include "../palette_manager.h"

#include <iostream>

extern int screenWidth;
extern int screenHeight;

Tetromino::Tetromino(float x, float y, int type) {
	switch (type) {
		case I:
			for (int i = 0; i < 4; i++) {
				Cube c(x, y + 20 * i);
				c.setSize(20, 20);
				c.setColor(PALETTE[1]);
				cubes.push_back(c);
			}
			break;
	}
}

void Tetromino::render(glm::mat4 proj) {
	for (Cube c : cubes) {
		c.render(proj);
	}
}

Tetromino::~Tetromino() {
}
