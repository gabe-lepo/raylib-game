#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "game/screen.h"
#include "objects.h"

typedef enum GroundedState
{
   GROUNDED_STATE_UNGROUNDED = 0,
   GROUNDED_STATE_GROUNDED
} GroundedState;

typedef struct Player
{
   // Object
   GameObject object;

   // Basic movement
   Vector2 velocity;
   Vector2 terminal_velocity;
   float move_speed;
   float sprint_speed_mod;
   float sneak_speed_mod;

   // Jumping mechanics
   GroundedState grounded;
   float gravity;
   float jump_speed;
   float max_jump_height;
   int max_jumps;
   int remaining_jumps;

   // Other
   Vector2 size;
} Player;

void InitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player *GetPlayer(void);
void CleanUpPlayer(void);

#endif