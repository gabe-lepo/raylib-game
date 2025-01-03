#include "start_menu.h"
#include "shared_menu_actions.h"
#include "game/game.h"
#include "game/game_state_stack.h"

// Unique actions
void NewGame(void)
{
   PushGameState(GAME_STATE_PLAYING);
}

void MyCloseGame(void)
{
   CloseGame();
}

// Objects
static MenuItem startMenuItems[] = {
    {"New Game", NewGame},
    {"Load Game", OpenLoad},    // Shared actions
    {"Settings", OpenSettings}, // Shared actions
    {"Close", MyCloseGame},
};

static Menu startMenu = {
    "Box Man",
    startMenuItems,
    sizeof(startMenuItems) / sizeof(startMenuItems[0]),
    0,
    BLACK,
};

// Getter func
Menu *GetStartMenu(void)
{
   return &startMenu;
}