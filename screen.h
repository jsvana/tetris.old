#ifndef __SCREEN_H
#define __SCREEN_H

#include <glm/glm.hpp>

class Screen {
public:
	virtual int update(unsigned int) = 0;
	virtual void render(glm::mat4 proj) = 0;

	virtual ~Screen() {
	}
};

#endif
