#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "screen.h"

#define PLAYER_DEFAULT_SPEED (int)5
#define PLAYER_DEFAULT_START_POSITION (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}
#define PLAYER_DEFAULT_SIZE (Vector2){SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT * 0.1f}

typedef struct Player {
   Rectangle rect;
   int speed;
   Color color;
} Player;

void InitPlayer(Player *player, Vector2 position, Vector2 size, int speed, Color color);
void UpdatePlayer(Player *player);
void DrawPlayer(Player *player);

#endif // PLAYER_H