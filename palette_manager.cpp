#include "palette_manager.h"

#include <iostream>

PaletteManager *PaletteManager::instance = nullptr;

PaletteManager::PaletteManager() {
}

PaletteManager *PaletteManager::getInstance() {
	if (PaletteManager::instance == nullptr) {
		PaletteManager::instance = new PaletteManager();
	}

	return PaletteManager::instance;
}

void PaletteManager::setPalette(std::vector<std::vector<float>> colors) {
	for (std::vector<float> &color : colors) {
		Color c(color[0], color[1], color[2]);
		palette.push_back(c);
	}
}
