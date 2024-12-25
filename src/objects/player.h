#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "game/screen.h"
#include "objects.h"

typedef enum isGrounded
{
   UNGROUNDED = 0,
   GROUNDED
} isGrounded;

typedef struct Player
{
   ObjectType objectType;
   Rectangle rect;
   Vector2 velocity;
   Color color;
   isGrounded grounded;
   float gravity;
   float jump_speed;
   float max_jump_height;
   int num_jumps;
   int remaining_jumps;
   float movement_delta;
   float movement_targetX;
} Player;

void InitPlayer(Player *player, Vector2 position, Vector2 size, Color color);
void UpdatePlayer(Player *player);
void DrawPlayer(Player *player);

#endif