#ifndef MENU_STACK_H
#define MENU_STACK_H

#include "menu.h"

void pushMenu(Menu *menu);
Menu *popMenu(void);
Menu *peekMenu(void);

#endif