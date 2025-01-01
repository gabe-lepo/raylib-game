#include "check_collisions.h"
#include "logging/log.h"
#include "utils/color_utils.h"

void CheckPlayerFloorCollision(Player *player, Floor floors[], size_t floorCount)
{
   Vector2 *playerCorners = player->object.corners;
   player->bottomCollide = false;

   for (size_t i = 0; i < floorCount; i++)
   {
      GameObject floor_object = floors[i].object;
      Vector2 *floorCorners = floor_object.corners;

      if (CheckCollisionRecs(player->object.shape.rectangle, floor_object.shape.rectangle))
      {
         // LogMessage(LOG_DEBUG, "Player collided somehow with floor {%s}", floor_object.label);

         // Player right side collides with left of floor
         if (playerCorners[1].x >= floorCorners[0].x &&
             playerCorners[1].x <= floorCorners[0].x + player->move_speed &&
             playerCorners[0].y < floorCorners[3].y &&
             playerCorners[2].y > floorCorners[0].y &&
             player->velocity.x > 0)
         {
            player->object.shape.rectangle.x = floor_object.shape.rectangle.x - player->object.shape.rectangle.width;
            player->velocity.x = 0.0f;
            LogMessage(LOG_DEBUG, "Player right collided with floor {%s}", floor_object.label);
         }

         // Player left side collides with right of floor
         if (playerCorners[0].x <= floorCorners[1].x &&
             playerCorners[0].x >= floorCorners[1].x - player->move_speed &&
             playerCorners[2].y > floorCorners[0].y &&
             playerCorners[0].y < floorCorners[3].y &&
             player->velocity.x < 0)
         {
            player->object.shape.rectangle.x = floor_object.shape.rectangle.x + floor_object.shape.rectangle.width;
            player->velocity.x = 0.0f;
            LogMessage(LOG_DEBUG, "Player left collided with floor {%s}", floor_object.label);
         }

         // Player bottom collides with top of floor
         if (playerCorners[2].y <= floorCorners[0].y &&
             playerCorners[2].y >= floorCorners[0].y - player->velocity.y &&
             playerCorners[0].x < floorCorners[1].x &&
             playerCorners[1].x > floorCorners[0].x &&
             player->velocity.y > 0)
         {
            player->object.shape.rectangle.y = floor_object.shape.rectangle.y - player->object.shape.rectangle.height;
            player->velocity.y = 0.0f;
            player->grounded = GROUNDED_STATE_GROUNDED;
            player->bottomCollide = true;
            LogMessage(LOG_DEBUG, "Player bottom collided with floor {%s}", floor_object.label);
         }

         // Player top collides with bottom of floor
         if (playerCorners[0].y <= floorCorners[2].y &&
             playerCorners[0].y >= floorCorners[2].y + player->velocity.y &&
             playerCorners[1].x > floorCorners[0].x &&
             playerCorners[0].x < floorCorners[1].x &&
             player->velocity.y < 0)
         {
            player->object.shape.rectangle.y = floor_object.shape.rectangle.y + floor_object.shape.rectangle.height;
            player->velocity.y = 0.0f;
            LogMessage(LOG_DEBUG, "Player top collided with floor {%s}", floor_object.label);
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