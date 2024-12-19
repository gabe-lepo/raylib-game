#include "raylib.h"
#include "game.h"
#include "screen.h"

int main(void)
{
   // Initialization
   InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
   SetTargetFPS(60);

   InitGame();

   int fps = GetFPS();

   // Main game loop
   while (!WindowShouldClose())
   {
      UpdateGame();

      BeginDrawing();
      ClearBackground(RAYWHITE);
      DrawGame();
      EndDrawing();
   }

   // Cleanup
   CloseGame();
   CloseWindow();
   return 0;
}
