#include "raylib.h"
#include "game/game.h"

int main(void)
{
   // Init game states
   InitGame();

   // Main game loop
   while (!WindowShouldClose() && !gameShouldClose)
   {
      // Update game states
      UpdateGame();

      // Draw the updates
      BeginDrawing();
      ClearBackground(RAYWHITE);
      DrawGame();
      EndDrawing();
   }

   // Cleanup
   CloseWindow();
   return 0;
}
