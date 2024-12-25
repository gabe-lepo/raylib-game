#include "check_collisions.h"
#include "logs/log.h"

void CheckPlayerCollision(Player *player, GameObject objects[], size_t objectCount)
{
   // This is causing cycling between grounded/ungrounded, but without it player cannot fall from floor
   // LogMessage(LOG_DEBUG, "PLAYER: Ungrounded due to initial object collision check");
   // player->grounded = UNGROUNDED;

   for (size_t i = 0; i < objectCount; i++)
   {
      GameObject *object = &objects[i];

      if (object->type == OBJECT_TYPE_COLLIDEABLE && CheckCollisionRecs(player->rect, object->rect))
      {
         // Vertical collision correction
         if (player->velocity.y > 0 && player->rect.y + player->rect.height <= object->rect.y + player->velocity.y)
         {
            player->rect.y = object->rect.y - player->rect.height;
            player->velocity.y = 0;
            LogMessage(LOG_DEBUG, "PLAYER: Grounded due to vertical object collision detection");
            player->grounded = GROUNDED;
         }

         // Horizontal collision correction
      }
   }
}