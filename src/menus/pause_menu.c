#include "pause_menu.h"
#include "shared_menu_actions.h"

// Actions
void resumeGame(void)
{
   // TODO
}
void saveGame(void)
{
   // TODO
}
void backToStart(void)
{
   // TODO
}

// Objects
static MenuItem pauseMenuItems[] = {
    {"Resume", resumeGame},
    {"Save", saveGame},
    {"Load", loadGame},
    {"Settings", openSettings},
    {"Exit", backToStart},
};

static Menu pauseMenu = {
    "Box Man",
    pauseMenuItems,
    sizeof(pauseMenuItems) / sizeof(pauseMenuItems[0]),
    0,
    0,
    BLACK,
};

// Getter func
Menu *getPauseMenu(void)
{
   return &pauseMenu;
}