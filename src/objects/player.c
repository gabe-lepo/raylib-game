#include "player.h"
#include "logging/log.h"
#include "utils/lerp.h"

void InitPlayer(Player *player, Vector2 position, Vector2 size, Color color)
{
   player->objectType = OBJECT_TYPE_COLLIDEABLE;
   player->rect.x = position.x;
   player->rect.y = position.y;
   player->rect.width = size.x;
   player->rect.height = size.y;
   player->velocity.x = 5.0f;
   player->velocity.y = 0.0f;
   player->color = color;
   player->grounded = UNGROUNDED;
   player->gravity = 0.7f;
   player->jump_speed = 15.0f;
   player->max_jump_height = player->rect.height * 2;
   player->num_jumps = 2;
   player->remaining_jumps = player->num_jumps;
}

void UpdatePlayer(Player *player)
{
   // Reapply some states based on grounding
   if (player->grounded)
   {
      LogMessage(LOG_DEBUG, "PLAYER: Grounded!");
      player->remaining_jumps = player->num_jumps;
      player->velocity.y = 0;
   }
   else
   {
      LogMessage(LOG_DEBUG, "PLAYER: Ungrounded!");
      player->velocity.y += player->gravity;
      player->rect.y += player->velocity.y;
   }

   // Check for ground collision at bottom of screen
   if (player->rect.y + player->rect.height >= SCREEN_HEIGHT)
   {
      player->rect.y = SCREEN_HEIGHT - player->rect.height;
      player->velocity.y = 0.0f;

      LogMessage(LOG_DEBUG, "PLAYER: Grounded due to collision at bottom of screen");
      player->grounded = GROUNDED;
   }

   // Check for ceiling collision
   if (player->rect.y <= 0)
   {
      player->rect.y = 0;
   }

   // Horizontal screen wrapping
   if (player->rect.x > SCREEN_WIDTH)
   {
      player->rect.x = 0;
   }
   if (player->rect.x < 0)
   {
      player->rect.x = SCREEN_WIDTH;
   }

   // Left/right movement controls
   float targetX = player->rect.x;
   if (IsKeyDown(KEY_RIGHT))
   {
      targetX += player->velocity.x;
   }
   if (IsKeyDown(KEY_LEFT))
   {
      targetX -= player->velocity.x;
   }
   player->rect.x = MyLerp(player->rect.x, targetX, 0.9f);

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
   DrawRectangleRec(player->rect, player->color);
}