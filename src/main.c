#include "raylib.h"
#include "game/game.h"
#include "log.h"

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
      ClearBackground(DARKGRAY);
      if (DrawGame())
      {
         break;
      }
      EndDrawing();
   }

   // Cleanup
   CloseWindow();
   CloseLog();
   return EXIT_SUCCESS;
}
