#include "raylib.h"
#include "game.h"
#include "screen.h"
#include "timer.h"
#include "log.h"
#include "menu.h"
#include "fps.h"

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
   InitMenus();
   InitTimer();

   // Main game loop
   while (!WindowShouldClose())
   {
      // Menu control
      if (IsKeyPressed(KEY_ESCAPE) && !isMenuActive(START_MENU))
      {
         ToggleMenu(PAUSE_MENU);
      }

      // State loop
      if (!isMenuActive(START_MENU) && !isMenuActive(PAUSE_MENU))
      {
         UpdateGame();
         UpdateTimer();
      }

      // Draw loop
      BeginDrawing();

      ClearBackground(DARKGRAY);
      if (isMenuActive(START_MENU))
      {
         UpdateStartMenu();
         DrawMenus();
      }
      else if (isMenuActive(PAUSE_MENU))
      {
         UpdatePauseMenu();
         DrawMenus();
      }
      else if (isMenuActive(SETTINGS_MENU))
      {
         UpdateSettingsMenu();
         DrawMenus();
      }
      else
      {
         DrawGame();
         DrawTimer();
         int fpsTextWidth = DrawMyFPS((SCREEN_WIDTH - fpsTextWidth) - 10, 10);
      }

      EndDrawing();
   }

   // Cleanup
   // CloseGame();
   CloseWindow();
   return 0;
}
