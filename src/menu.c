#include "menu.h"
#include "raylib.h"

// Defaults for menu on game start
static int menuActive = 1;
static float menuAlpha = 1.0f;

void InitMenu(void)
{
   menuActive = 1;
   menuAlpha = 1.0f;
}

void ToggleMenu(void)
{
   if (menuActive)
   {
      menuActive = 0;
   }
   else
   {
      menuActive = 1;
   }
}

void DrawMenu(void)
{
   if (menuActive)
   {
      DrawRectangle(
          0,
          0,
          GetScreenWidth(),
          GetScreenHeight(),
          Fade(BLACK, menuAlpha));

      int screenWidth = GetScreenWidth();
      int screenHeight = GetScreenHeight();
      int menuItemPosY = screenHeight / 2 - 60;
      int menuItemPosX = screenWidth / 2 - MeasureText("Box Man", 40) / 2;

      DrawText("Box Man", menuItemPosX, menuItemPosY, 40, RAYWHITE);
      menuItemPosY += 60;
      DrawText("1. Save", screenWidth / 2 - MeasureText("1. Save", 20) / 2, menuItemPosY, 20, WHITE);
      menuItemPosY += 40;
      DrawText("2. Load", screenWidth / 2 - MeasureText("2. Load", 20) / 2, menuItemPosY, 20, WHITE);
      menuItemPosY += 40;
      DrawText("3. Close", screenWidth / 2 - MeasureText("3. Close", 20) / 2, menuItemPosY, 20, WHITE);
   }
}

int isMenuActive(void)
{
   return menuActive;
}