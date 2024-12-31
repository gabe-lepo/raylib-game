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
         // Check for vertical collision
         if (CheckCollisionRecs(player->object.shape.rectangle, floor_object.shape.rectangle))
         {
            colliding = true;
            LogMessage(LOG_DEBUG, "Player collided with object {%s}", floor_object.label);

            // Vertical collision: Player landing on top of the object
            if (player->velocity.y >= 0 &&
                player->object.shape.rectangle.y + player->object.shape.rectangle.height <= floor_object.shape.rectangle.y + player->velocity.y)
            {
               player->object.shape.rectangle.y = floor_object.shape.rectangle.y - player->object.shape.rectangle.height + 0.1;
               player->velocity.y = 0;
               player->grounded = GROUNDED_STATE_GROUNDED;
               LogMessage(LOG_DEBUG, "Player grounded due to vertical object collision");

               if (player->object.shape.rectangle.x > floor_object.shape.rectangle.x + floor_object.shape.rectangle.width ||
                   player->object.shape.rectangle.x + player->object.shape.rectangle.width < floor_object.shape.rectangle.x)
               {
                  colliding = false;
               }
            }
         }
      }
   }
   if (!colliding)
      player->grounded = GROUNDED_STATE_UNGROUNDED;
}