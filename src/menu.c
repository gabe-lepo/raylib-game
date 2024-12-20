#include "menu.h"
#include "raylib.h"
#include "screen.h"

static int menuActive;
int selectedMenuItem;

void InitMenu(void)
{
   menuActive = 1;
   selectedMenuItem = 0;
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

void UpdateMenu(void)
{
   if (IsKeyPressed(KEY_DOWN))
   {
      selectedMenuItem++;
      if (selectedMenuItem > 2)
      {
         selectedMenuItem = 0;
      }
   }
   if (IsKeyPressed(KEY_UP))
   {
      selectedMenuItem--;
      if (selectedMenuItem < 0)
      {
         selectedMenuItem = 2;
      }
   }
}

void DrawMenu(void)
{
   if (menuActive)
   {
      DrawRectangle(
          0,
          0,
          SCREEN_WIDTH,
          SCREEN_HEIGHT,
          BLACK);

      int menuItemPosY = SCREEN_HEIGHT / 2 - 60;
      int menuItemPosX = SCREEN_WIDTH / 2 - MeasureText("Box Man", 40) / 2;

      // Menu colors
      Color titleColor = RAYWHITE;
      Color saveColor = (selectedMenuItem == 0) ? YELLOW : WHITE;
      Color loadColor = (selectedMenuItem == 1) ? YELLOW : WHITE;
      Color closeColor = (selectedMenuItem == 2) ? YELLOW : WHITE;

      // Menu title
      DrawText("Box Man", menuItemPosX, menuItemPosY, 40, RAYWHITE);
      menuItemPosY += 60;

      // Menu options
      DrawText("Save", SCREEN_WIDTH / 2 - MeasureText("Save", 20) / 2, menuItemPosY, 20, saveColor);
      menuItemPosY += 40;

      DrawText("Load", SCREEN_WIDTH / 2 - MeasureText("Load", 20) / 2, menuItemPosY, 20, loadColor);
      menuItemPosY += 40;

      DrawText("Close", SCREEN_WIDTH / 2 - MeasureText("Close", 20) / 2, menuItemPosY, 20, closeColor);
   }
}

int isMenuActive(void)
{
   return menuActive;
}