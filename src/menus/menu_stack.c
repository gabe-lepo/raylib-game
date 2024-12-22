#include "menu_stack.h"

#define MAX_MENU_STACK_SIZE 16

static Menu *menuStack[MAX_MENU_STACK_SIZE];
static int menuStackTop = -1;

void pushMenu(Menu *menu)
{
   if (menuStackTop < MAX_MENU_STACK_SIZE - 1)
   {
      menuStack[++menuStackTop] = menu;
      menu->isActive = 1;
   }
}

Menu *popMenu(void)
{
   if (menuStackTop >= 0)
   {
      Menu *menu = menuStack[menuStackTop--];
      menu->isActive = 0;
      return menu;
   }

   return NULL;
}

Menu *peekMenu(void)
{
   if (menuStackTop >= 0)
   {
      return menuStack[menuStackTop];
   }

   return NULL;
}