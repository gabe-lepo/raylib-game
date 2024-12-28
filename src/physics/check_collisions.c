#include "check_collisions.h"
#include "logging/log.h"

void CheckPlayerCollision(Player *player, GameObject objects[], size_t objectCount)
{
   for (size_t i = 0; i < objectCount; i++)
   {
      GameObject *object = &objects[i];

      // Check for collisions with only collideable objects
      if (player->object.type == OBJECT_TYPE_COLLIDEABLE &&
          object->type == OBJECT_TYPE_COLLIDEABLE)
      {
         // Check for vertical collision
         if (CheckCollisionRecs(player->object.shape.rectangle, object->shape.rectangle))
         {
            LogMessage(LOG_DEBUG, "Player collided with object");

            // Vertical collision: Player landing on top of the object
            if (player->velocity.y > 0 &&
                player->object.shape.rectangle.y + player->object.shape.rectangle.height <= object->shape.rectangle.y + player->velocity.y)
            {
               player->object.shape.rectangle.y = object->shape.rectangle.y - player->object.shape.rectangle.height;
               player->velocity.y = 0;
               LogMessage(LOG_DEBUG, "Player grounded due to vertical object collision");
               player->grounded = GROUNDED_STATE_GROUNDED;
            }
         }

         // Check if player is no longer touching top of the object
         bool isOverlappingHorizontally =
             (player->object.shape.rectangle.x < object->shape.rectangle.x + object->shape.rectangle.width) &&
             (player->object.shape.rectangle.x + player->object.shape.rectangle.width > object->shape.rectangle.x);

         bool isTouchingVertically =
             (player->object.shape.rectangle.y + player->object.shape.rectangle.height == object->shape.rectangle.y);

         if (isTouchingVertically && !isOverlappingHorizontally)
         {
            // Player moved off the object horizontally
            player->grounded = GROUNDED_STATE_UNGROUNDED;
            LogMessage(LOG_DEBUG, "Player ungrounded due to moving off object");
         }
      }
   }

   // If the player is ungrounded, apply gravity
   if (player->grounded == GROUNDED_STATE_UNGROUNDED)
   {
      LogMessage(LOG_DEBUG, "Player falling due to being ungrounded");
      player->velocity.y += player->gravity;
   }
}