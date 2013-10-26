#pragma once

#ifndef __PALETTE_MANAGER_H
#define __PALETTE_MANAGER_H

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "util.h"

#include <vector>

class PaletteManager {
private:
	std::vector<Color> palette;

	static PaletteManager *instance;

	PaletteManager();
	~PaletteManager();

public:
	static PaletteManager *getInstance();

	void setPalette(std::vector<std::vector<float>> colors);

	std::vector<Color> getPalette() {
		return palette;
	}

	void destroy();
};

#define PALETTE (PaletteManager::getInstance()->getPalette())

#endif
