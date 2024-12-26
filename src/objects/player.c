#include "player.h"
#include "logging/log.h"
#include "utils/lerp.h"

// #include "math.h"

void InitPlayer(Player *player, Vector2 position, Vector2 size, Color color)
{
   player->objectType = OBJECT_TYPE_COLLIDEABLE;
   player->rect.x = position.x;
   player->rect.y = position.y;
   player->rect.width = size.x;
   player->rect.height = size.y;
   player->velocity.x = 0.0f;
   player->velocity.y = 0.0f;
   player->color = color;
   player->grounded = UNGROUNDED;
   player->gravity = 0.5f;
   player->sprint_speed_mod = 2.0f;
   player->sneak_speed_mod = 0.5f;
   player->jump_speed = 15.0f;
   player->max_jump_height = player->rect.height * 2;
   player->num_jumps = 2;
   player->remaining_jumps = player->num_jumps;
   player->terminal_velocity.x = 50.0f; // PLaceholder
   player->terminal_velocity.y = 15.0f;
}

void UpdatePlayer(Player *player)
{
   // Reapply some states based on grounding
   if (player->grounded)
   {
      player->remaining_jumps = player->num_jumps;
      player->velocity.y = 0;
   }
   else
   {
      // Apply terminal y velocity
      if (!(player->velocity.y >= player->terminal_velocity.y))
      {
         player->velocity.y += player->gravity;
      }
      else
      {
         player->velocity.y = player->terminal_velocity.y;
      }

      // Apply final y velocity
      player->rect.y += player->velocity.y;
   }

   // Check for ground collision at bottom of screen
   if (player->rect.y + player->rect.height >= SCREEN_DIMENSIONS.y)
   {
      player->rect.y = SCREEN_DIMENSIONS.y - player->rect.height;
      player->velocity.y = 0.0f;
      player->grounded = GROUNDED;

      LogMessage(LOG_DEBUG, "Player grounded due to collision at bottom of screen");
   }

   // Check for ceiling collision
   if (player->rect.y - player->rect.height <= 0)
   {
      player->rect.y = 0 + player->rect.height;
      player->velocity.y = 0.0f;
      LogMessage(LOG_DEBUG, "Player hit the ceiling");
   }

   // Left/right movement controls
   player->move_speed = 5.0f; // Reset move speed every frame

   // Sprint/sneaking modifiers
   if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
      player->move_speed *= player->sprint_speed_mod;

   if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))
      player->move_speed *= player->sneak_speed_mod;

   if (IsKeyDown(KEY_RIGHT))
      player->velocity.x = player->move_speed;

   if (IsKeyDown(KEY_LEFT))
      player->velocity.x = -(player->move_speed);

   if (!IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT))
      player->velocity.x = 0.0f;

   // Apply velocity
   player->rect.x += player->velocity.x;

   // Horizontal screen collision (must be done after horizontal movement checks)
   if (player->rect.x + player->rect.width >= SCREEN_DIMENSIONS.x)
   {
      player->rect.x = SCREEN_DIMENSIONS.x - player->rect.width - SCREEN_EDGE_PADDING;
   }
   if (player->rect.x <= 0)
   {
      player->rect.x = SCREEN_EDGE_PADDING;
   }

   // Multi jump logic
   if (IsKeyPressed(KEY_SPACE) && player->remaining_jumps > 0)
   {
      LogMessage(LOG_DEBUG, "PLAYER: Ungrounded due to space bar jump");
      player->grounded = UNGROUNDED;
      player->velocity.y = -(player->jump_speed);
      player->remaining_jumps--;
   }
}

void DrawPlayer(Player *player)
{
   // Object
   DrawRectangleRec(player->rect, player->color);

   // Player info text
   int textWidth = MeasureText(TextFormat("Position: %.2fx%.2f", SCREEN_DIMENSIONS.x, SCREEN_DIMENSIONS.y), 20);

   DrawText(
       TextFormat(
           "Position: %.2fx%.2f\nWall Offsets: %.2f - %.2f\nVelocity: %.2fx%.2f\nTerminal_V: %s\nGrounded: %s\nJumps: %d",
           player->rect.x,
           player->rect.y,
           0 + player->rect.x,
           SCREEN_DIMENSIONS.x - player->rect.x,
           player->velocity.x,
           player->velocity.y,
           player->velocity.y >= player->terminal_velocity.y ? "Yes" : "No",
           player->grounded > 0 ? "GROUNDED" : "UNGROUNDED",
           player->remaining_jumps),
       SCREEN_DIMENSIONS.x / 2 - textWidth / 2,
       10,
       20,
       BLACK);
}