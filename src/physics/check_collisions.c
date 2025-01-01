#include "check_collisions.h"
#include "logging/log.h"
#include "utils/color_utils.h"

void CheckPlayerFloorCollision(Player *player, Floor floors[], size_t floorCount)
{
   for (size_t i = 0; i < floorCount; i++)
   {
      GameObject floor_object = floors[i].object;

      // Check for collisions with only collideable objects
      if (player->object.type == OBJECT_TYPE_COLLIDEABLE &&
          floor_object.type == OBJECT_TYPE_COLLIDEABLE)
      {
         if (floor_object.shape.rectangle.x <= player->object.shape.rectangle.x &&
             floor_object.shape.rectangle.x + floor_object.shape.rectangle.width >= player->object.shape.rectangle.x &&
             floor_object.shape.rectangle.y >= player->object.shape.rectangle.y &&
             floor_object.shape.rectangle.y <= player->object.shape.rectangle.y + player->object.shape.rectangle.height &&
             player->velocity.y > 0)
         {
            player->velocity.y = 0.0f;
            player->object.shape.rectangle.y = floor_object.shape.rectangle.y - player->object.shape.rectangle.height;
            break;
         }
      }
   }
}

void CheckPlayerChunkCollision(Player *player, Chunk chunks[], size_t chunkCount)
{
   for (size_t i = 0; i < chunkCount; i++)
   {
      GameObject chunk_object = chunks[i].object;

      if (player->object.type == OBJECT_TYPE_COLLIDEABLE &&
          chunk_object.type == OBJECT_TYPE_COLLIDEABLE)
      {
         if (CheckCollisionRecs(player->object.shape.rectangle, chunk_object.shape.rectangle))
         {
            player->object.color = GetComplimentaryColor(chunk_object.color);
         }
      }
   }
}