#ifndef __SCREEN_H
#define __SCREEN_H

class Screen {
public:
	virtual int update(unsigned int) = 0;
	virtual void render() = 0;

	virtual ~Screen() = 0;
};

#endif
