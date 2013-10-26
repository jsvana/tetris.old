#include "tetromino.h"

#include "../palette_manager.h"

#include <iostream>

Tetromino::Tetromino(float x, float y, int type) {
	switch (type) {
		case I:
			for (int i = 0; i < 4; i++) {
				Cube c(x, y + .25 * i);
				c.setSize(.125, .125);
				c.setColor(PALETTE[1]);
				cubes.push_back(c);
			}
			break;
	}
}

void Tetromino::render() {
	for (Cube c : cubes) {
		c.render();
	}
}

Tetromino::~Tetromino() {
}
