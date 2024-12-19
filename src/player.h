#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "screen.h"

#define PLAYER_DEFAULT_SPEED (int)5

typedef struct Player
{
   Rectangle rect;
   int speed;
   Color color;
} Player;

void InitPlayer(Player *player, Vector2 position, Vector2 size, int speed, Color color);
void UpdatePlayer(Player *player);
void DrawPlayer(Player *player);

#endif // PLAYER_H