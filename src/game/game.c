#include "raylib.h"
#include "game/game.h"
#include "game/game_state_stack.h"
#include "player.h"
#include "timer.h"
#include "fps.h"
#include "screen.h"
#include "menus/start_menu.h"
#include "menus/pause_menu.h"
#include "menus/settings_menu.h"
#include "menus/load_menu.h"
#include "log.h"

#include <stdlib.h>

static Player player1;
static Menu *startMenu;
static Menu *pauseMenu;
static Menu *settingsMenu;
static Menu *loadMenu;

GameState gameState;
GameStateStack stateStack;
int gameShouldClose = 0;

void InitGame()
{
   // Setup logs
   if (InitLog())
   {
      CloseGame();
   }
   // SetTraceLogCallback(WriteLog);
   LogMessage(LOG_DEBUG, "InitGame():");

   // Setup game state
   gameState = GAME_STATE_START_MENU;
   InitGameStateStack(&stateStack);
   PushGameState(&stateStack, gameState);
   LogMessage(LOG_DEBUG, "\tGame state and state stack initialized");

   // Window init
   InitScreenSize();
   // SetConfigFlags(FLAG_WINDOW_RESIZABLE); // Resizeable window
   InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
   LogMessage(LOG_DEBUG, "\tWindow initialized");

   // Other setup stuff
   SetExitKey(KEY_NULL); // Must be called after InitWindow
   SetTargetFPS(60);
   LogMessage(LOG_DEBUG, "\tFPS counter initialized");

   // Timer
   InitTimer();
   // FPS init?
   LogMessage(LOG_DEBUG, "\tTimer counter initialized");

   // Player init
   Vector2 startPosition = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
   Vector2 size = {SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT * 0.1f};
   InitPlayer(
       &player1,
       startPosition,
       size,
       PLAYER_DEFAULT_SPEED,
       BLUE);
   LogMessage(LOG_DEBUG, "\tPlayer initialized");

   // Menu init
   startMenu = getStartMenu();
   pauseMenu = getPauseMenu();
   settingsMenu = getSettingsMenu();
   loadMenu = getLoadMenu();
   LogMessage(LOG_DEBUG, "\tMenus initialized");
}

int UpdateGame(void)
{
   switch (gameState)
   {
   case GAME_STATE_START_MENU:
      LogMessage(LOG_DEBUG, "Game State: START_MENU");
      updateMenu(startMenu);
      break;
   case GAME_STATE_PLAYING:
      LogMessage(LOG_DEBUG, "Game State: PLAYING");

      // Open pause menu
      if (IsKeyPressed(KEY_ESCAPE))
      {
         gameState = GAME_STATE_PAUSE_MENU;
         PushGameState(&stateStack, gameState);
      }

      // Normal game updates
      UpdatePlayer(&player1);
      UpdateTimer();
      break;
   case GAME_STATE_PAUSE_MENU:
      LogMessage(LOG_DEBUG, "Game State: PAUSE_MENU");
      updateMenu(pauseMenu);
      break;
   case GAME_STATE_SETTINGS_MENU:
      LogMessage(LOG_DEBUG, "Game State: SETTINGS_MENU");
      updateMenu(settingsMenu);
      break;
   case GAME_STATE_LOAD_MENU:
      LogMessage(LOG_DEBUG, "Game State: LOAD_MENU");
      updateMenu(loadMenu);
      break;
   default:
      LogMessage(LOG_ERROR, "Can't update game, game state is undefined, exiting.");
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}

int DrawGame(void)
{
   switch (gameState)
   {
   case GAME_STATE_START_MENU:
      if (drawMenu(startMenu))
      {
         return EXIT_FAILURE;
      }
      break;
   case GAME_STATE_PLAYING:
      DrawPlayer(&player1);
      DrawTimer();
      int fpsTextWidth = DrawMyFPS((SCREEN_WIDTH - fpsTextWidth) - 10, 10);
      break;
   case GAME_STATE_PAUSE_MENU:
      if (drawMenu(pauseMenu))
      {
         return EXIT_FAILURE;
      }
      break;
   case GAME_STATE_SETTINGS_MENU:
      if (drawMenu(settingsMenu))
      {
         return EXIT_FAILURE;
      }
      break;
   case GAME_STATE_LOAD_MENU:
      if (drawMenu(loadMenu))
      {
         return EXIT_FAILURE;
      }
      break;
   default:
      LogMessage(LOG_ERROR, "Can't draw game, game state is undefined, exiting.");
      return EXIT_FAILURE;
      break;
   }

   return EXIT_SUCCESS;
}

void CloseGame(void)
{
   ClearGameStateStack(&stateStack);
   gameShouldClose = 1;
}