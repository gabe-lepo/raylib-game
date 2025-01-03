#include "pause_menu.h"
#include "shared_menu_actions.h"
#include "game/game_state_stack.h"

// Actions
void ResumeGame(void)
{
   PopGameState();
   PushGameState(GAME_STATE_PLAYING);
}
void SaveGame(void)
{
   // TODO
}

// Objects
static MenuItem pauseMenuItems[] = {
    {"Resume", ResumeGame},
    {"Save", SaveGame},
    {"Load", OpenLoad},
    {"Settings", OpenSettings},
    {"Exit", BackUpMenu},
};

static Menu pauseMenu = {
    "Pause",
    pauseMenuItems,
    sizeof(pauseMenuItems) / sizeof(pauseMenuItems[0]),
    0,
    BLACK,
};

// Getter func
Menu *GetPauseMenu(void)
{
   return &pauseMenu;
}