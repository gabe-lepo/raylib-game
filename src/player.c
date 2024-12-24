#include "player.h"

#define MAX_JUMP_HEIGHT 32
#define JUMP_SPEED 1

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
   if (IsKeyDown(KEY_RIGHT))
      player->rect.x += player->speed;
   if (IsKeyDown(KEY_LEFT))
      player->rect.x -= player->speed;
   if (IsKeyDown(KEY_UP))
      player->rect.y -= player->speed;
   if (IsKeyDown(KEY_DOWN))
      player->rect.y += player->speed;

   if (IsKeyDown(KEY_SPACE))
   {
      float start_y = player->rect.y;

      for (int i = 0; i <= MAX_JUMP_HEIGHT; i += JUMP_SPEED)
      {
         player->rect.y--;
      }
      for (int i = 0; i >= start_y; i -= JUMP_SPEED)
      {
         player->rect.y++;
      }
   }
}

void DrawPlayer(Player *player)
{
   DrawRectangleRec(player->rect, player->color);
}