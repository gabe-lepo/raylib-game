#ifndef MENU_H
#define MENU_H

#include "raylib.h"
#include "logging/log.h"
#include "game/screen.h"

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
   Color backgroundColor;
} Menu;

void ToggleMenu(Menu *menu);
void UpdateMenu(Menu *menu);
int DrawMenu(Menu *menu);

#endif // MENU_H