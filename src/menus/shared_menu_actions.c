#include "shared_menu_actions.h"
#include "game/game_state_stack.h"

// For load and settings menus, don't pop the game state we need to remember the last parent-menu
void OpenLoad(void)
{
   PushGameState(GAME_STATE_LOAD_MENU);
}

void OpenSettings(void)
{
   PushGameState(GAME_STATE_SETTINGS_MENU);
}

void BackUpMenu(void)
{
   PopGameState();
}