#include "raylib.h"
#include "game.h"
#include "screen.h"
#include "timer.h"
#include "log.h"
#include "menu.h"

#include <stdio.h>

int main(void)
{
   // Initialization
   SetTraceLogCallback(WriteLog);
   InitScreenSize();
   // SetConfigFlags(FLAG_WINDOW_RESIZABLE); // Resizeable window
   InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
   SetExitKey(KEY_NULL); // Must be called after InitWindow
   SetTargetFPS(60);

   InitGame();
   InitTimer();
   InitMenu();

   // int fps = GetFPS();

   // Main game loop
   while (!WindowShouldClose())
   {
      // Menu
      if (IsKeyPressed(KEY_ESCAPE))
      {
         ToggleMenu();
      }

      // State loop
      if (!isMenuActive())
      {
         UpdateGame();
         UpdateTimer();
      }

      // Draw loop
      BeginDrawing();

      ClearBackground(RAYWHITE);
      if (isMenuActive())
      {
         DrawMenu();
      }
      else
      {
         DrawGame();
         DrawTimer();
      }

      EndDrawing();
   }

   // Cleanup
   // CloseGame();
   CloseWindow();
   return 0;
}
