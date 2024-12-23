#include "pause_menu.h"
#include "shared_menu_actions.h"
#include "game/game_state_stack.h"

// Actions
void resumeGame(void)
{
   LogMessage(LOG_INFO, "Resuming game");
   PushGameState(GAME_STATE_PLAYING);
}
void saveGame(void)
{
   // TODO
}
void backToStart(void)
{
   LogMessage(LOG_INFO, "Going back to start menu");
   PushGameState(GAME_STATE_START_MENU);
}

// Objects
static MenuItem pauseMenuItems[] = {
    {"Resume", resumeGame},
    {"Save", saveGame},
    {"Load", openLoad},
    {"Settings", openSettings},
    {"Exit", backToStart},
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