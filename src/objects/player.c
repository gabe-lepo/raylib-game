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
   player->velocity.x = 5.0f;
   player->velocity.y = 0.0f;
   player->color = color;
   player->grounded = UNGROUNDED;
   player->gravity = 0.7f;
   player->jump_speed = 15.0f;
   player->max_jump_height = player->rect.height * 2;
   player->num_jumps = 2;
   player->remaining_jumps = player->num_jumps;
   player->movement_delta = 0.9f;
   player->movement_targetX = player->rect.x;
}

void UpdatePlayer(Player *player)
{
   // Reapply some states based on grounding
   if (player->grounded)
   {
      // LogMessage(LOG_DEBUG, "PLAYER: Grounded!");
      player->remaining_jumps = player->num_jumps;
      player->velocity.y = 0;
   }
   else
   {
      // LogMessage(LOG_DEBUG, "PLAYER: Ungrounded!");
      player->velocity.y += player->gravity;
      player->rect.y += player->velocity.y;
   }

   // Check for ground collision at bottom of screen
   if (player->rect.y + player->rect.height >= SCREEN_DIMENSIONS.y)
   {
      player->rect.y = SCREEN_DIMENSIONS.y - player->rect.height;
      player->velocity.y = 0.0f;

      // LogMessage(LOG_DEBUG, "PLAYER: Grounded due to collision at bottom of screen");
      player->grounded = GROUNDED;
   }

   // Check for ceiling collision
   if (player->rect.y - player->rect.height <= 0)
   {
      player->rect.y = 0 + player->rect.height;
      player->velocity.y = 0.0f;
      // LogMessage(LOG_DEBUG, "PLAYER: Hit the ceiling!");
   }

   // Horizontal screen collision
   if (player->rect.x + player->rect.width >= SCREEN_DIMENSIONS.x)
   {
      LogMessage(LOG_DEBUG,
                 "Stopping player movement at right screen boundary\n\tRectX %.2f - %.2f",
                 player->rect.x,
                 player->rect.x + player->rect.width);

      player->rect.x = SCREEN_DIMENSIONS.x - player->rect.width;
      player->velocity.x = 0.0f;
      player->movement_targetX = player->rect.x;
   }
   if (player->rect.x <= 0)
   {
      LogMessage(LOG_DEBUG,
                 "Stopping player movement at left screen boundary\n\tRectX %.2f - %.2f",
                 player->rect.x,
                 player->rect.x + player->rect.width);
      player->rect.x = 0;
      player->velocity.x = 0.0f;
      player->movement_targetX = player->rect.x;
   }

   // Left/right movement controls
   if (IsKeyDown(KEY_RIGHT) && player->rect.x + player->rect.width < SCREEN_DIMENSIONS.x)
   {
      player->movement_targetX += player->velocity.x;
   }
   if (IsKeyDown(KEY_LEFT) && player->rect.x > 0)
   {
      player->movement_targetX -= player->velocity.x;
   }

   // Clamp movement targetX to ensure plyer stays within screen bounds
   if (player->movement_targetX < 0)
   {
      player->movement_targetX = 0;
   }
   if (player->movement_targetX + player->rect.width > SCREEN_DIMENSIONS.x)
   {
      player->movement_targetX = SCREEN_DIMENSIONS.x - player->rect.width;
   }

   // Smoothly interpolate player x position
   player->rect.x = MyLerp(player->rect.x, player->movement_targetX, player->movement_delta);

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

   // Position text
   int x = player->rect.x;
   int y = player->rect.y;
   int size = 20;
   DrawText(TextFormat("%dx%d", x, y), x - player->rect.width, y - size, size, BLACK);
}