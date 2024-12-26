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
   player->gravity = 0.7f;
   player->move_speed = 7.5f;
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
   }
   if (player->rect.x <= 0)
   {
      LogMessage(LOG_DEBUG,
                 "Stopping player movement at left screen boundary\n\tRectX %.2f - %.2f",
                 player->rect.x,
                 player->rect.x + player->rect.width);
      player->rect.x = 0;
      player->velocity.x = 0.0f;
   }

   // Left/right movement controls
   if (IsKeyDown(KEY_RIGHT) && player->rect.x + player->rect.width < SCREEN_DIMENSIONS.x)
   {
      player->velocity.x = player->move_speed;
      player->rect.x += player->velocity.x;
   }
   else if (IsKeyDown(KEY_LEFT) && player->rect.x > 0)
   {
      player->velocity.x = -(player->move_speed);
      player->rect.x += player->velocity.x;
   }
   else
   {
      player->velocity.x = 0.0f;
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

   // Position text
   // int posX = player->rect.x;
   // int posY = player->rect.y;
   // int velocityX = player->velocity.x;
   // int velocityY = player->velocity.y;
   int size = 20;
   int textWidth = MeasureText(TextFormat("Position:\t%.2fx%.2f", SCREEN_DIMENSIONS.x, SCREEN_DIMENSIONS.y), size);
   DrawText(
       TextFormat(
           "Position:\t\t%.2fx%.2f\nVelocity:\t%.2fx%.2f\nGrounded:\t%s\nJumps:\t%d",
           player->rect.x,
           player->rect.y,
           player->velocity.x,
           player->velocity.y,
           player->grounded > 0 ? "GROUNDED" : "UNGROUNDED",
           player->remaining_jumps),
       SCREEN_DIMENSIONS.x / 2 - textWidth / 2,
       0 + 10,
       size,
       BLACK);
}