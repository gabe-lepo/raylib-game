#include "fps.h"

// Modified from raylib/src/rtext.c to return as text width
int DrawMyFPS(int posX, int posY)
{
   Color color = LIME; // Good FPS
   int fps = GetFPS();

   if ((fps < 30) && (fps >= 15))
      color = ORANGE; // Warning FPS
   else if (fps < 15)
      color = RED; // Low FPS

   DrawText(TextFormat("%2i FPS", fps), posX, posY, 20, color);

   return MeasureText(TextFormat("%2i FPS", fps), 20);
}