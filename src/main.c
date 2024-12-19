#include "/Users/glepoutre/Documents/vscode/raylib/src/raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450
#define SCREEN_TITLE "Raylib Graphics"

int main(void)
{
   // Initialization
   InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
   SetTargetFPS(60);

   // Main game loop
   while (!WindowShouldClose())
   {
      BeginDrawing();
      ClearBackground(WHITE);
      DrawText("Congrats! You created your first window!", (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 20, LIGHTGRAY);
      EndDrawing();
   }

   // Cleanup
   CloseWindow();
   return 0;
}
