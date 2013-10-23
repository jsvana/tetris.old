#ifndef __MAIN_SCREEN_H
#define __MAIN_SCREEN_H

#include "../screen.h"

typedef struct {

} MainScreenData;

Screen *mainScreenCreate();

int mainScreenUpdate(Screen *s, unsigned int ticks);
void mainScreenRender(Screen *s);

void mainScreenDestroy(Screen *s);

#endif
