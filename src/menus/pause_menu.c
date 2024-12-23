#include "pause_menu.h"
#include "shared_menu_actions.h"
#include "game/game_state_stack.h"

// Actions
void resumeGame(void)
{
   PopGameState();
   PushGameState(GAME_STATE_PLAYING);
}
void saveGame(void)
{
   // TODO
}

// Objects
static MenuItem pauseMenuItems[] = {
    {"Resume", resumeGame},
    {"Save", saveGame},
    {"Load", openLoad},
    {"Settings", openSettings},
    {"Exit", backUpMenu},
};

static Menu pauseMenu = {
    "Pause",
    pauseMenuItems,
    sizeof(pauseMenuItems) / sizeof(pauseMenuItems[0]),
    0,
    BLACK,
};

// Getter func
Menu *getPauseMenu(void)
{
   return &pauseMenu;
}