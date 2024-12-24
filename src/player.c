#include "player.h"
#include "log.h"

#define MAX_JUMP_HEIGHT 32
#define JUMP_SPEED 0.5

void InitPlayer(Player *player, Vector2 position, Vector2 size, int speed, Color color)
{
   player->rect.x = position.x;
   player->rect.y = position.y;
   player->rect.width = size.x;
   player->rect.height = size.y;
   player->speed = speed;
   player->color = color;
}

void UpdatePlayer(Player *player)
{
   if (player->rect.x > SCREEN_WIDTH)
   {
      player->rect.x = 0;
   }
   if (player->rect.x < 0)
   {
      player->rect.x = SCREEN_WIDTH;
   }
   if (player->rect.y > SCREEN_HEIGHT)
   {
      player->rect.y = 0;
   }
   if (player->rect.y < 0)
   {
      player->rect.y = SCREEN_HEIGHT;
   }

   if (IsKeyDown(KEY_RIGHT))
   {
      LogMessage(LOG_DEBUG, "PLAYER: Moving right");
      player->rect.x += player->speed;
   }
   if (IsKeyDown(KEY_LEFT))
   {
      LogMessage(LOG_DEBUG, "PLAYER: Moving left");
      player->rect.x -= player->speed;
   }
   if (IsKeyDown(KEY_UP))
   {
      LogMessage(LOG_DEBUG, "PLAYER: Moving up");
      player->rect.y -= player->speed;
   }
   if (IsKeyDown(KEY_DOWN))
   {
      LogMessage(LOG_DEBUG, "PLAYER: Moving down");
      player->rect.y += player->speed;
   }

   if (IsKeyPressed(KEY_SPACE))
   {
      // TODO
   }
}

void DrawPlayer(Player *player)
{
   DrawRectangleRec(player->rect, player->color);
}