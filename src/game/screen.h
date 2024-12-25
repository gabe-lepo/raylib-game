#ifndef SCREEN_H
#define SCREEN_H

#include "raylib.h"

#define SCREEN_TITLE "Box Man"
#define WINDOW_MONITOR_RATIO 0.8f
#define SCREEN_EDGE_PADDING 10

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

void InitScreenSize(void);

#endif // SCREEN_H