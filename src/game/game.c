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

static Player player1;
static Menu *startMenu;
static Menu *pauseMenu;
static Menu *settingsMenu;
static Menu *loadMenu;

GameState currentGameState = GAME_STATE_START_MENU;
int gameShouldClose = 0;

void InitGame()
{
   // Setup logs
   SetTraceLogCallback(WriteLog);

   // Window init
   InitScreenSize();
   // SetConfigFlags(FLAG_WINDOW_RESIZABLE); // Resizeable window
   InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

   // Other setup stuff
   SetExitKey(KEY_NULL); // Must be called after InitWindow
   SetTargetFPS(60);

   // Timer
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
}

void UpdateGame(void)
{
   switch (currentGameState)
   {
   case GAME_STATE_START_MENU:
      updateMenu(startMenu);
      break;
   case GAME_STATE_PLAYING:
      // Normal game updates
      UpdatePlayer(&player1);
      UpdateTimer();

      // Open pause menu
      if (IsKeyPressed(KEY_ESCAPE))
      {
         currentGameState = GAME_STATE_PAUSE_MENU;
      }
      break;
   case GAME_STATE_PAUSE_MENU:
      updateMenu(pauseMenu);
      break;
   case GAME_STATE_SETTINGS_MENU:
      updateMenu(settingsMenu);
      break;
   case GAME_STATE_LOAD_MENU:
      updateMenu(loadMenu);
      break;
   default:
      LogMessage(LOG_FATAL, "Can't update game, game state is undefined, exiting.");
      CloseGame();
      break;
   }
}

void DrawGame(void)
{
   switch (currentGameState)
   {
   case GAME_STATE_START_MENU:
      drawMenu(startMenu);
      break;
   case GAME_STATE_PLAYING:
      DrawPlayer(&player1);
      DrawTimer();
      int fpsTextWidth = DrawMyFPS((SCREEN_WIDTH - fpsTextWidth) - 10, 10);
      break;
   case GAME_STATE_PAUSE_MENU:
      drawMenu(pauseMenu);
      break;
   case GAME_STATE_SETTINGS_MENU:
      drawMenu(settingsMenu);
      break;
   case GAME_STATE_LOAD_MENU:
      drawMenu(loadMenu);
      break;
   default:
      LogMessage(LOG_FATAL, "Can't draw game, game state is undefined, exiting.");
      CloseGame();
      break;
   }
}

void CloseGame(void)
{
   gameShouldClose = 1;
}