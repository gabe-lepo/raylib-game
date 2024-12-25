#ifndef FPS_H
#define FPS_H

#include "raylib.h"

#define TARGET_FPS 60

typedef struct FPSText
{
   int fps;
   Color color;
   int size;
   Vector2 position; // Must type cast to int when drawing
} FPSText;

void InitFPS(void);
void UpdateFPS(void);
void DrawMyFPS(void);

#endif