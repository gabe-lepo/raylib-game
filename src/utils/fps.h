#ifndef FPS_H
#define FPS_H

#include "raylib.h"

typedef struct FPSText
{
   int fps;
   Color color;
   int size;
   Vector2 position; // Must type cast to int when drawing
} FPSText;

void InitFPS(int target_fps);
void UpdateFPS(void);
void DrawMyFPS(void);

#endif