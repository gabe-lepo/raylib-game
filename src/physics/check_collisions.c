#include "check_collisions.h"
#include "logging/log.h"

void CheckPlayerFloorCollision(Player *player, Floor floors[], size_t floorCount)
{
   bool colliding;
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
            colliding = true;
            player->velocity.y = 0.0f;
            player->object.shape.rectangle.y = floor_object.shape.rectangle.y - player->object.shape.rectangle.height;
            break;
         }
         else
         {
            colliding = false;
         }
      }
   }
}