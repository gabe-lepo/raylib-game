#include "fps.h"
#include "game/screen.h"

void InitFPS(void)
{
   SetTargetFPS(TARGET_FPS);
}

void UpdateFPS(void)
{
   // TODO
}

// Improved/modified from raylib's rtext.c
void DrawMyFPS(void)
{
   // Values
   int fps = GetFPS();
   Color color = LIME;

   // Positioning
   int textWidth = MeasureText(TextFormat("%2i FPS", fps), FPS_TEXT_SIZE);
   int posX = SCREEN_WIDTH - textWidth - SCREEN_EDGE_PADDING;
   int posY = 0 + SCREEN_EDGE_PADDING;

   // Colors
   if (fps < (int)(TARGET_FPS * 0.5) && fps >= (int)(TARGET_FPS * 0.25))
   {
      color = ORANGE;
   }
   else if (fps < (int)(TARGET_FPS * 0.25))
   {
      color = RED;
   }

   // Draw it
   DrawText(TextFormat("%2i FPS", fps), posX, posY, FPS_TEXT_SIZE, color);
}