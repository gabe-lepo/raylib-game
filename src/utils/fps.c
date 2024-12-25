#include "fps.h"
#include "game/screen.h"

static FPSText fpsText;

void InitFPS(void)
{
   SetTargetFPS(TARGET_FPS);
   fpsText.fps = TARGET_FPS;
   fpsText.size = 20;
   int textWidth = MeasureText(TextFormat("%2i FPS", fpsText.fps), fpsText.size);
   fpsText.position.x = SCREEN_WIDTH - textWidth - SCREEN_EDGE_PADDING;
   fpsText.position.y = 0 + SCREEN_EDGE_PADDING;
   fpsText.color = LIME;
}

void UpdateFPS(void)
{
   fpsText.fps = GetFPS();
   int textWidth = MeasureText(TextFormat("%2i FPS", fpsText.fps), fpsText.size);

   if (fpsText.fps < (int)(TARGET_FPS * 0.5) && fpsText.fps >= (int)(TARGET_FPS * 0.25))
   {
      fpsText.color = ORANGE;
   }
   else if (fpsText.fps < (int)(TARGET_FPS * 0.25))
   {
      fpsText.color = RED;
   }

   fpsText.color = LIME;
}

// Improved/modified from raylib's rtext.c
void DrawMyFPS(void)
{
   DrawText(TextFormat("%2i FPS", fpsText.fps), fpsText.position.x, fpsText.position.y, fpsText.size, fpsText.color);
}