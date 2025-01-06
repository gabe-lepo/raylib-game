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
#include "objects/screen_chunks.h"
#include "camera/game_camera.h"
#include "objects/particles/particle.h"
#include "objects/particles/player_particles.h"
#include "shaders/background_shader.h"

#include <stdlib.h>

#define DEBUG_LOGS 1
#define RAYLIB_LOGS 1

#define STACK_PRINT_TIME_S_MOD 10

// Object pointers
// Menus
static Menu *startMenu;
static Menu *pauseMenu;
static Menu *settingsMenu;
static Menu *loadMenu;

// Sound
// static Music mainMenuSong;

// Objects
Player *p_player;

Floor *p_floors;
static int floorCount;

Chunk *p_chunks;
static int chunkCount;
static int chunkXCount;
static int chunkYCount;
static bool colorfulChunks = true;

int gameShouldClose = 0;
int updateGameIterations = 0;

static int target_fps = 60; // Changing this drastically effects physics!
static size_t target_seed = 1735706498;

void InitGame()
{
   // Setup logs
   if (InitLog(DEBUG_LOGS, RAYLIB_LOGS))
      CloseGame();
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
   InitSeed(target_seed);

   // Menu init
   startMenu = GetStartMenu();
   pauseMenu = GetPauseMenu();
   settingsMenu = GetSettingsMenu();
   loadMenu = GetLoadMenu();

   // Init screen chunks
   InitChunks(colorfulChunks);
   p_chunks = GetChunks(&chunkCount, &chunkXCount, &chunkYCount);

   // Floor init
   InitFloors();
   p_floors = GetFloors(&floorCount);

   // Player init
   InitPlayer();
   p_player = GetPlayer();

   // Init camera
   InitGameCamera(p_player);

   // Music init
   // InitMusic();
   // StartMusic(mainMenuSong);

   // Particles!
   InitPlayerParticles(1000);

   // Parallax background
   // InitParallaxBackground();

   // Player shader
   if (InitShader())
      CloseGame();

   // Must be done last!
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
      CheckPlayerFloorCollision(p_player, p_floors, floorCount);
      // CheckPlayerChunkCollision(p_player, p_chunks, chunkCount); // Recolors player
      // UpdateChunks();
      // UpdateParallaxBackground(p_player->velocity.x);
      UpdateFloors(p_player);
      UpdateShader();
      UpdatePlayer();
      UpdatePlayerParticles(GetFrameTime());
      UpdateGameCamera(p_player);
      UpdateFPS();
      UpdateTimer();
      break;
   case GAME_STATE_START_MENU:
      UpdateMenu(startMenu);
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
      UpdateMenu(pauseMenu);
      break;
   case GAME_STATE_SETTINGS_MENU:
      UpdateMenu(settingsMenu);
      break;
   case GAME_STATE_LOAD_MENU:
      UpdateMenu(loadMenu);
      break;
   default:
      LogMessage(LOG_ERROR, "Can't update game, undefined game state!");
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}

int DrawGame(void)
{
   // Things that need to happen in all states but playing state
   if (PeekGameState() != GAME_STATE_PLAYING)
   {
      CenterGameCamera();
   }

   // Full game state cases
   switch (PeekGameState())
   {
   case GAME_STATE_INIT:
      break;
   case GAME_STATE_PLAYING:
      ClearBackground(DARKGRAY);
      // DrawChunks();
      DrawShader(); // Background shader
      DrawTimer();
      DrawMyFPS();
      DrawFloors();
      DrawPlayerParticles();
      DrawPlayer();
      break;
   case GAME_STATE_START_MENU:
      if (DrawMenu(startMenu))
      {
         return EXIT_FAILURE;
      }
      break;
   case GAME_STATE_PAUSE_MENU:
      if (DrawMenu(pauseMenu))
      {
         return EXIT_FAILURE;
      }
      break;
   case GAME_STATE_SETTINGS_MENU:
      if (DrawMenu(settingsMenu))
      {
         return EXIT_FAILURE;
      }
      break;
   case GAME_STATE_LOAD_MENU:
      if (DrawMenu(loadMenu))
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
   CleanUpPlayer();
   CleanupPlayerParticles();
   CleanupParticleSystem();
   CleanUpFloors();
   CleanUpChunks();
   // CleanupParallaxBackground();
   ClearGameStateStack();
   gameShouldClose = 1;
}