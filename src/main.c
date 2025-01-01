#include "raylib.h"
#include "game/game.h"
#include "logging/log.h"
#include "camera/game_camera.h"

#include <stdlib.h>

static GameCamera *p_gameCamera;

int main(void)
{
   // Init game states
   InitGame();

   // GameCamera pointer to pass to raylib's cam init
   p_gameCamera = GetGameCamera();

   // Main game loop
   while (!WindowShouldClose() && !gameShouldClose)
   {
      // Update game states
      if (UpdateGame())
      {
         break;
      }

      // Draw the updates
      BeginDrawing();
      BeginMode2D(p_gameCamera->camera2d);
      if (DrawGame())
      {
         break;
      }
      EndMode2D();
      EndDrawing();
   }

   // Cleanup
   CloseWindow();
   CloseLog();
   return EXIT_SUCCESS;
}
