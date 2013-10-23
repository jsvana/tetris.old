#ifndef __SCREEN_H
#define __SCREEN_H

#define MAIN_SCREEN 0

typedef struct Screen Screen;

typedef int (*updateFunc)(Screen *, unsigned int);
typedef void (*renderFunc)(Screen *);

struct Screen {
	int type;
	updateFunc update;
	renderFunc render;
	void *data;
};

#endif
