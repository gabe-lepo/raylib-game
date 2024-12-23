#include "raylib.h"
#include "game/game.h"
#include "game/game_state_stack.h"
#include "timer.h"
#include "fps.h"
#include "screen.h"
#include "menus/start_menu.h"
#include "menus/pause_menu.h"
#include "menus/settings_menu.h"
#include "menus/load_menu.h"
#include "log.h"
#include "objects/objects.h"
#include "objects/floor.h"
#include "objects/player.h"
#include "physics/check_collisions.h"

#include <stdlib.h>

#define DEBUG_LOGS 1
#define RAYLIB_LOGS 1

#define TARGET_FPS 60
#define STACK_PRINT_TIME_S_MOD 10

static Player player1;
static Menu *startMenu;
static Menu *pauseMenu;
static Menu *settingsMenu;
static Menu *loadMenu;

int gameShouldClose = 0;
int updateGameIterations = 0;

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
   SetTargetFPS(TARGET_FPS);
   InitTimer();
   // FPS init?

   // Floor init
   InitFloor();

   // Player init
   float basicSize = 50.0f;
   Vector2 size = {basicSize, basicSize};
   Vector2 startPosition = {SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT - basicSize - 100};
   InitPlayer(
       &player1,
       startPosition,
       size,
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
   // Print out contents of state stack occasionally
   updateGameIterations++;
   if (updateGameIterations == TARGET_FPS * STACK_PRINT_TIME_S_MOD)
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
      GameObject objects[] = {*getFloor()};
      size_t objectCount = sizeof(objects) / sizeof(objects[0]);
      CheckPlayerCollision(&player1, objects, objectCount);
      UpdatePlayer(&player1);
      UpdateTimer();
      break;
   case GAME_STATE_START_MENU:
      updateMenu(startMenu);
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
      DrawFloor();
      DrawPlayer(&player1);
      DrawTimer();
      int fpsTextWidth = DrawMyFPS((SCREEN_WIDTH - fpsTextWidth) - 10, 10);
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

void CloseGame(void)
{
   LogMessage(LOG_INFO, "Closing game");
   ClearGameStateStack();
   gameShouldClose = 1;
}