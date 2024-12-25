#ifndef FPS_H
#define FPS_H

#include "raylib.h"

#define TARGET_FPS 60
#define FPS_TEXT_SIZE 20

void InitFPS(void);
void UpdateFPS(void);
void DrawMyFPS(void);

#endif