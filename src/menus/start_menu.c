#include "start_menu.h"
#include "shared_menu_actions.h"

// Actions
void newGame(void)
{
   LogMessage(LOG_INFO, "Starting a new game");
}

void closeGame(void)
{
   // TODO
}

// Objects
static MenuItem startMenuItems[] = {
    {"New Game", newGame},
    {"Load Game", loadGame},
    {"Settings", openSettings},
    {"Close", closeGame},
};

static Menu startMenu = {
    "Box Man",
    startMenuItems,
    sizeof(startMenuItems) / sizeof(startMenuItems[0]),
    0,
    1,
    BLACK,
};

// Getter func
Menu *getStartMenu(void)
{
   return &startMenu;
}