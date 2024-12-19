#include "raylib.h"
#include "game.h"
#include "player.h"

static Player player1;

void InitGame(void)
{
   InitPlayer(
       &player1,
       PLAYER_DEFAULT_START_POSITION,
       PLAYER_DEFAULT_SIZE,
       PLAYER_DEFAULT_SPEED,
       BLUE);
}

void UpdateGame(void)
{
   UpdatePlayer(&player1);
}

void DrawGame(void)
{
   DrawPlayer(&player1);
}

void CloseGame(void)
{
   // Nothing to do here
}