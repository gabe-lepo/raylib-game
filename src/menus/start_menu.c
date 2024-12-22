#include "start_menu.h"
#include "shared_menu_actions.h"
#include "game/game.h"
#include "game/game_state_stack.h"

// Unique actions
void newGame(void)
{
   LogMessage(LOG_INFO, "Starting a new game.");
   currentGameState = GAME_STATE_PLAYING;
}

void closeGame(void)
{
   LogMessage(LOG_INFO, "Closing game.");
   CloseGame();
}

// Objects
static MenuItem startMenuItems[] = {
    {"New Game", newGame},
    {"Load Game", openLoad},    // Shared actions
    {"Settings", openSettings}, // Shared actions
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