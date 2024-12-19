#include "player.h"

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
}

void DrawPlayer(Player *player)
{
   DrawRectangleRec(player->rect, player->color);
}