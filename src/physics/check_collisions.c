#include "check_collisions.h"
#include "logging/log.h"

void CheckPlayerCollision(Player *player, GameObject objects[], size_t objectCount)
{
   for (size_t i = 0; i < objectCount; i++)
   {
      GameObject *object = &objects[i];

      // Check for collisions with only collideable objects
      if (player->objectType == OBJECT_TYPE_COLLIDEABLE &&
          object->type == OBJECT_TYPE_COLLIDEABLE)
      {
         // Check for vertical collision
         if (CheckCollisionRecs(player->rect, object->rect))
         {
            LogMessage(LOG_DEBUG, "Player collided with object");

            // Vertical collision: Player landing on top of the object
            if (player->velocity.y > 0 &&
                player->rect.y + player->rect.height <= object->rect.y + player->velocity.y)
            {
               player->rect.y = object->rect.y - player->rect.height;
               player->velocity.y = 0;
               LogMessage(LOG_DEBUG, "Player grounded due to vertical object collision");
               player->grounded = GROUNDED;
            }
         }

         // Check if player is no longer touching top of the object
         bool isOverlappingHorizontally =
             (player->rect.x < object->rect.x + object->rect.width) &&
             (player->rect.x + player->rect.width > object->rect.x);

         bool isTouchingVertically =
             (player->rect.y + player->rect.height == object->rect.y);

         if (isTouchingVertically && !isOverlappingHorizontally)
         {
            // Player moved off the object horizontally
            player->grounded = UNGROUNDED;
            LogMessage(LOG_DEBUG, "Player ungrounded due to moving off object");
         }
      }
   }

   // If the player is ungrounded, apply gravity
   if (player->grounded == UNGROUNDED)
   {
      LogMessage(LOG_DEBUG, "Player falling due to being ungrounded");
      player->velocity.y += player->gravity;
   }
}