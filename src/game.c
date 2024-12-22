#include "raylib.h"
#include "game.h"
#include "player.h"
#include "timer.h"
#include "fps.h"
#include "screen.h"
#include "menus/start_menu.h"
#include "menus/pause_menu.h"
#include "menus/settings_menu.h"

typedef enum
{
   GAME_STATE_PLAYING,
   GAME_STATE_START_MENU,
   GAME_STATE_PAUSE_MENU,
   GAME_STATE_SETTINGS_MENU,
} GameState;
GameState currentGameState;

static Player player1;
static Menu *startMenu;
static Menu *pauseMenu;
static Menu *settingsMenu;

int gameShouldClose = 0;

void InitGame(void)
{
   // Setup logs
   SetTraceLogCallback(WriteLog);

   // Window init
   InitScreenSize();
   // SetConfigFlags(FLAG_WINDOW_RESIZABLE); // Resizeable window
   InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
   SetExitKey(KEY_NULL); // Must be called after InitWindow
   SetTargetFPS(60);

   // Timer
   InitTimer();

   // Game state init
   currentGameState = GAME_STATE_START_MENU;

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
}

void UpdateGame(void)
{
   switch (currentGameState)
   {
   case GAME_STATE_PLAYING:
      // Normal game updates
      UpdatePlayer(&player1);
      UpdateTimer();

      // Open pause menu
      if (IsKeyPressed(KEY_ESCAPE))
      {
         currentGameState = GAME_STATE_PAUSE_MENU;
         toggleMenu(pauseMenu);
      }
      break;
   case GAME_STATE_START_MENU:
      updateMenu(startMenu);
      if (!startMenu->isActive)
      {
         currentGameState = GAME_STATE_PLAYING;
      }
      break;

   case GAME_STATE_PAUSE_MENU:
      updateMenu(pauseMenu);
      if (!pauseMenu->isActive)
      {
         currentGameState = GAME_STATE_PLAYING;
      }
      break;
   case GAME_STATE_SETTINGS_MENU:
      updateMenu(settingsMenu);
      if (!settingsMenu->isActive)
      {
         currentGameState = GAME_STATE_PAUSE_MENU;
      }
      break;
   default:
      break;
   }
}

void DrawGame(void)
{
   switch (currentGameState)
   {
   case GAME_STATE_PLAYING:
      DrawPlayer(&player1);
      DrawTimer();
      int fpsTextWidth = DrawMyFPS((SCREEN_WIDTH - fpsTextWidth) - 10, 10);
      break;
   case GAME_STATE_START_MENU:
      drawMenu(startMenu);
      break;
   case GAME_STATE_PAUSE_MENU:
      drawMenu(pauseMenu);
      break;
   case GAME_STATE_SETTINGS_MENU:
      drawMenu(settingsMenu);
      break;
   default:
      break;
   }
}

void CloseGame(void)
{
   gameShouldClose = 1;
}