#include "raylib.h"
#include "game/game.h"
#include "logging/log.h"

#include <stdlib.h>

int main(void)
{
   // Init game states
   InitGame();

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
