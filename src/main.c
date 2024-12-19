#include "raylib.h"
#include "game.h"
#include "screen.h"
#include "timer.h"
#include "log.h"

#include <stdio.h>

int main(void)
{
   // Initialization
   SetTraceLogCallback(WriteLog);
   InitScreenSize();
   fflush(stdout);                        // Screen size debugging
   SetConfigFlags(FLAG_WINDOW_RESIZABLE); // Resizeable window
   InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
   SetTargetFPS(60);

   InitGame();
   InitTimer();

   // int fps = GetFPS();

   // Main game loop
   while (!WindowShouldClose())
   {
      // State loop
      UpdateGame();
      UpdateTimer();

      // Draw loop
      BeginDrawing();

      ClearBackground(RAYWHITE);
      DrawGame();
      DrawTimer();

      EndDrawing();
   }

   // Cleanup
   // CloseGame();
   CloseWindow();
   return 0;
}
