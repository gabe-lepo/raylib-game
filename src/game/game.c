#include "raylib.h"
#include "game/game.h"
#include "game/game_state_stack.h"
#include "utils/timer.h"
#include "utils/fps.h"
#include "game/screen.h"
#include "menus/start_menu.h"
#include "menus/pause_menu.h"
#include "menus/settings_menu.h"
#include "menus/load_menu.h"
#include "logging/log.h"
#include "objects/objects.h"
#include "objects/floor.h"
#include "objects/player.h"
#include "physics/check_collisions.h"
// #include "audio/music.h"
#include "utils/seed.h"

#include <stdlib.h>
#include <time.h> // For random seed for floors

#define DEBUG_LOGS 1
#define RAYLIB_LOGS 1

#define STACK_PRINT_TIME_S_MOD 10

/**
 * @todo Need to clean up these object definitions. I.e. does player1
 * really need to be "global" by being defined here. Should it (and maybe
 * other objects) be scoped to their unique functionality files (player.c)?
 *
 */
static Player player1;
static GameObject floors[10];
static unsigned int floorSeed = 0;
static Menu *startMenu;
static Menu *pauseMenu;
static Menu *settingsMenu;
static Menu *loadMenu;
// static Music mainMenuSong;

int gameShouldClose = 0;
int updateGameIterations = 0;

static int target_fps = 60;

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
   InitStartScreen();
   InitMainScreen();

   // Other setup stuff
   SetExitKey(KEY_NULL); // Must be called after InitWindow
   InitFPS(target_fps);
   InitTimer();
   InitSeed(123456789);

   // Floor init
   InitFloors();

   // Player init
   InitPlayer();

   // Music init
   // InitMusic();
   // StartMusic(mainMenuSong);

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
   // Print out contents of state stack occasionally
   updateGameIterations++;
   if (updateGameIterations == target_fps * STACK_PRINT_TIME_S_MOD)
   {
      const GameStateStack *stack = getStateStack();
      LogMessage(LOG_INFO, "Contents of game state stack:");
      for (size_t i = 0; i < stack->top; i++)
      {
         LogMessage(LOG_INFO, "\tStack Index: {%zu} | State {%s}", i, StateToString(stack->states[i]));
      }
      updateGameIterations = 0;
   }

   switch (PeekGameState())
   {
   case GAME_STATE_INIT:
      break;
   case GAME_STATE_PLAYING:
      // Open pause menu
      if (IsKeyPressed(KEY_ESCAPE))
      {
         PopGameState();
         PushGameState(GAME_STATE_PAUSE_MENU);
      }

      // Normal routine
      CheckPlayerCollision(&player1, floors, sizeof(floors) / sizeof(floors[0]));
      UpdatePlayer();
      UpdateFPS();
      UpdateTimer();
      break;
   case GAME_STATE_START_MENU:
      updateMenu(startMenu);
      // if (IsKeyPressed(KEY_P))
      //    UpdateMusic(mainMenuSong, true);
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
   case GAME_STATE_PLAYING:
      ClearBackground(DARKGRAY);
      DrawTimer();
      DrawMyFPS();
      DrawPlayer();
      DrawFloors();
      break;
   case GAME_STATE_START_MENU:
      if (drawMenu(startMenu))
      {
         return EXIT_FAILURE;
      }
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

void CloseGame()
{
   LogMessage(LOG_INFO, "Closing game");
   // Cleanup object labels
   ClearGameStateStack();
   gameShouldClose = 1;
}