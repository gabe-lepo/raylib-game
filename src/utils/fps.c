#include "fps.h"
#include "game/screen.h"

static FPSText fpsText;
static int TARGET_FPS;

/**
 * @brief Initialize raylib target FPS, setup FPSText struct for drawing.
 * @param target_fps Int number for desired FPS, 0 for 60.
 * @return void - Operates on internal FPSText struct.
 */
void InitFPS(int target_fps)
{
   if (!target_fps)
      TARGET_FPS = 60;
   else
      TARGET_FPS = target_fps;

   SetTargetFPS(TARGET_FPS);
   fpsText.fps = TARGET_FPS;
   fpsText.size = 20;
   int textWidth = MeasureText(TextFormat("%2i FPS", fpsText.fps), fpsText.size);
   fpsText.position.x = SCREEN_DIMENSIONS.x - textWidth - SCREEN_EDGE_PADDING;
   fpsText.position.y = 0 + SCREEN_EDGE_PADDING;
   fpsText.color = LIME;
}

/**
 * @brief Update FPSText struct with actual FPS, determine text color and width for positioning.
 * @return void - Operate on internal FPSText struct.
 */
void UpdateFPS(void)
{
   fpsText.fps = GetFPS();
   if (fpsText.fps >= (int)(TARGET_FPS * 0.75))
   {
      fpsText.color = LIME;
   }
   else if (fpsText.fps < (int)(TARGET_FPS * 0.75) && fpsText.fps >= (int)(TARGET_FPS * 0.25))
   {
      fpsText.color = ORANGE;
   }
   else if (fpsText.fps < (int)(TARGET_FPS * 0.25))
   {
      fpsText.color = RED;
   }
   else
   {
      fpsText.color = BLACK;
   }

   int textWidth = MeasureText(TextFormat("%2i FPS", fpsText.fps), fpsText.size);
   fpsText.position.x = SCREEN_DIMENSIONS.x - textWidth - SCREEN_EDGE_PADDING;
}

/**
 * @brief Draw the FPSText structure. Improved from raylib's DrawFPS().
 * @return void - Operate on internal FPSText struct
 */
void DrawMyFPS(void)
{
   DrawText(TextFormat("%2i FPS", fpsText.fps), fpsText.position.x, fpsText.position.y, fpsText.size, fpsText.color);
}