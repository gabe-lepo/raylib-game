#include "menu.h"
#include "logs/log.h"

#include <stdlib.h>

// Menu control funcs
void toggleMenu(Menu *menu)
{
   // TODO
}

void updateMenu(Menu *menu)
{
   // Validate menu structure
   if (menu == NULL)
   {
      LogMessage(LOG_ERROR, "Menu {%s} not initialized!", menu->title);
   }
   if (menu->items == NULL || menu->itemCount == 0)
   {
      LogMessage(LOG_ERROR, "Menu {%s} has no items!", menu->title);
   }

   // Item selection
   if (IsKeyPressed(KEY_DOWN))
   {
      // LogMessage(LOG_DEBUG, "INCREASING index of menu:{%s} from index:{%d}...", menu->title, menu->selectedItemIndex);
      menu->selectedItemIndex++;
      if (menu->selectedItemIndex > menu->itemCount - 1)
      {
         menu->selectedItemIndex = 0;
      }
      // LogMessage(LOG_DEBUG, "\t...to index:{%d}", menu->selectedItemIndex);
   }

   if (IsKeyPressed(KEY_UP))
   {
      // LogMessage(LOG_DEBUG, "DECREASING index of menu:{%s} from index:{%d}...", menu->title, menu->selectedItemIndex);
      if ((int)menu->selectedItemIndex <= 0) // Cast from size_t for signed comparison
      {
         menu->selectedItemIndex = menu->itemCount - 1;
      }
      else
      {
         menu->selectedItemIndex--;
      }
      // LogMessage(LOG_DEBUG, "\t...to index:{%d}", menu->selectedItemIndex);
   }

   // Item action
   if (IsKeyPressed(KEY_ENTER))
   {
      menu->items[menu->selectedItemIndex].action();
   }
}

int drawMenu(Menu *menu)
{
   // Background
   DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, menu->backgroundColor);

   // Title
   int titleSize = 60;
   int menuItemPosY = SCREEN_HEIGHT / 2 - titleSize;
   int menuItemPosX = SCREEN_WIDTH / 2 - MeasureText(menu->title, titleSize) / 2;

   DrawText(menu->title, menuItemPosX, menuItemPosY, titleSize, RAYWHITE);
   menuItemPosY += titleSize;

   // Items
   Color textColor;
   int textSize = 30;
   for (int i = 0; i < menu->itemCount; i++)
   {
      // Re-center items
      menuItemPosX = SCREEN_WIDTH / 2 - MeasureText(menu->items[i].label, textSize) / 2;

      // Check if item is selected
      textColor = WHITE;
      if (i == menu->selectedItemIndex)
      {
         textColor = YELLOW;
      }

      // Draw it
      DrawText(menu->items[i].label, menuItemPosX, menuItemPosY, textSize, textColor);

      // Padding between next item
      menuItemPosY += textSize;
   }

   return EXIT_SUCCESS;
}