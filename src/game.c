#include "raylib.h"
#include "game.h"
#include "player.h"

int gameShouldClose = 0;

static Player player1;

void InitGame(void)
{
   Vector2 startPosition = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
   Vector2 size = {SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT * 0.1f};
   InitPlayer(
       &player1,
       startPosition,
       size,
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
   gameShouldClose = 1;
}