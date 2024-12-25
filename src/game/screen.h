#ifndef SCREEN_H
#define SCREEN_H

#include "raylib.h"

#define SCREEN_TITLE "Box Man"
#define WINDOW_MONITOR_RATIO 1.0f
#define SCREEN_EDGE_PADDING 10

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

void InitStartScreen(void);
void InitMainScreen(void);

#endif