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
   // Visuals
   ObjectType objectType;
   Rectangle rect;
   Color color;

   // Basic movement
   Vector2 velocity;
   Vector2 terminal_velocity;
   float move_speed;
   float sprint_speed_mod;
   float sneak_speed_mod;

   // Jumping mechanics
   isGrounded grounded;
   float gravity;
   float jump_speed;
   float max_jump_height;
   int num_jumps;
   int remaining_jumps;
} Player;

void InitPlayer(Player *player, Vector2 position, Vector2 size, Color color);
void UpdatePlayer(Player *player);
void DrawPlayer(Player *player);

#endif