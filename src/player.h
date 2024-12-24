#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "screen.h"

typedef enum isGrounded
{
   UNGROUNDED = 0,
   GROUNDED
} isGrounded;

typedef struct Player
{
   Rectangle rect;
   Vector2 velocity;
   Color color;
   isGrounded grounded;
   float gravity;
   float jump_speed;
   float max_jump_height;
} Player;

void InitPlayer(Player *player, Vector2 position, Vector2 size, Color color);
void UpdatePlayer(Player *player);
void DrawPlayer(Player *player);

#endif // PLAYER_H