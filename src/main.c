#include "raylib.h"
#include "game.h"
#include "screen.h"
#include "timer.h"

int main(void)
{
   // Initialization
   InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
   SetTargetFPS(60);

   InitGame();
   InitTimer();

   int fps = GetFPS();

   // Main game loop
   while (!WindowShouldClose())
   {
      UpdateGame();
      UpdateTimer();

      BeginDrawing();
      ClearBackground(RAYWHITE);
      DrawGame();
      DrawTimer();
      EndDrawing();
   }

   // Cleanup
   CloseGame();
   CloseWindow();
   return 0;
}
