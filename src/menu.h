#ifndef MENU_H
#define MENU_H

#include "raylib.h"
#include "screen.h"
#include "log.h"
#include "game.h"

#define START_MENU 0
#define PAUSE_MENU 1
#define SETTINGS_MENU 2

void ResetMenuSelections(void);
void InitMenus(void);
void ToggleMenu(int menu);
void UpdateStartMenu(void);
void UpdatePauseMenu(void);
void UpdateSettingsMenu(void);
void DrawMenus(void);
int isMenuActive(int menu);

#endif // MENU_H