#ifndef MENU_H
#define MENU_H

#include "raylib.h"
#include "screen.h"
#include "log.h"
#include "game.h"

typedef struct Menu Menu;
typedef struct MenuOptions MenuOptions;
typedef struct MenuOptionsFunctions MenuOptionsFunctions;

typedef struct
{
   const char *title;
   MenuOptions *options[];

   // Menu control/display functionality:
   // void InitMenus(void)
} Menu;

typedef struct
{
   const char *name;
   MenuOptionsFunctions *function;
} MenuOptions;

typedef struct
{

} MenuOptionsFunctions;

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