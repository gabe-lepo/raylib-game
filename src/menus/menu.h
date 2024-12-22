#ifndef MENU_H
#define MENU_H

#include "raylib.h"
#include "log.h"
#include "screen.h"

#include <stddef.h>

typedef struct MenuItem
{
   const char *label;
   void (*action)(void);
} MenuItem;

typedef struct Menu
{
   const char *title;
   MenuItem *items;
   size_t itemCount;
   size_t selectedItemIndex;
   int isActive;
   Color backgroundColor;
} Menu;

void toggleMenu(Menu *menu);
void updateMenu(Menu *menu);
void drawMenu(Menu *menu);

#endif // MENU_H