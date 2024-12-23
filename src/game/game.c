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

#define DEBUG_LOGS 1
#define RAYLIB_LOGS 0

static Player player1;
static Menu *startMenu;
static Menu *pauseMenu;
static Menu *settingsMenu;
static Menu *loadMenu;

int gameShouldClose = 0;

void InitGame()
{
   // Setup logs
   if (InitLog(DEBUG_LOGS, RAYLIB_LOGS))
   {
      CloseGame();
   }
   LogMessage(LOG_INFO, "InitGame start");

   // Setup game state
   InitGameStateStack();

   // Window init
   InitScreenSize();
   // SetConfigFlags(FLAG_WINDOW_RESIZABLE); // Resizeable window
   InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

   // Other setup stuff
   SetExitKey(KEY_NULL); // Must be called after InitWindow
   SetTargetFPS(60);
   InitTimer();
   // FPS init?

   // Player init
   Vector2 startPosition = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
   Vector2 size = {SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT * 0.1f};
   InitPlayer(
       &player1,
       startPosition,
       size,
       PLAYER_DEFAULT_SPEED,
       BLUE);

   // Menu init
   startMenu = getStartMenu();
   pauseMenu = getPauseMenu();
   settingsMenu = getSettingsMenu();
   loadMenu = getLoadMenu();

   PopGameState();
   PushGameState(GAME_STATE_START_MENU);
   LogMessage(LOG_INFO, "InitGame done");
}

int UpdateGame(void)
{
   switch (PeekGameState())
   {
   case GAME_STATE_INIT:
      break;
   case GAME_STATE_START_MENU:
      updateMenu(startMenu);
      break;
   case GAME_STATE_PLAYING:
      // Open pause menu
      if (IsKeyPressed(KEY_ESCAPE))
      {
         PopGameState();
         PushGameState(GAME_STATE_PAUSE_MENU);
      }

      // Normal routine
      UpdatePlayer(&player1);
      UpdateTimer();
      break;
   case GAME_STATE_PAUSE_MENU:
      if (IsKeyPressed(KEY_ESCAPE))
      {
         PopGameState();
         PushGameState(GAME_STATE_PLAYING);
      }

      // Normal routine
      updateMenu(pauseMenu);
      break;
   case GAME_STATE_SETTINGS_MENU:
      updateMenu(settingsMenu);
      break;
   case GAME_STATE_LOAD_MENU:
      updateMenu(loadMenu);
      break;
   default:
      LogMessage(LOG_ERROR, "Can't update game, undefined game state!");
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}

int DrawGame(void)
{
   switch (PeekGameState())
   {
   case GAME_STATE_INIT:
      break;
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
      LogMessage(LOG_ERROR, "Can't draw game, undefined game state!");
      return EXIT_FAILURE;
      break;
   }

   return EXIT_SUCCESS;
}

void CloseGame(void)
{
   LogMessage(LOG_INFO, "Closing game");
   ClearGameStateStack();
   gameShouldClose = 1;
}