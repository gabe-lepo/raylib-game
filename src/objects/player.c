#include "player.h"
#include "logging/log.h"
#include "objects/particles/player_particles.h"
#include "utils/color_utils.h"

#include <stdlib.h>
#include <string.h>

static Player player;
static Vector2 playerCenter;

void InitPlayer(void)
{
   // Init player as 50x50 px rectangle
   player.size = (Vector2){50.0f, 50.0f};
   Vector2 playerStartPosition = {SCREEN_DIMENSIONS.x / 2, (float)SCREEN_DIMENSIONS.y - player.size.y - 100};
   playerCenter = (Vector2){player.object.shape.rectangle.x + (player.object.shape.rectangle.width / 2.0f),
                            player.object.shape.rectangle.y + (player.object.shape.rectangle.height / 2.0f)};

   Shape playerShape = {
       .type = SHAPE_TYPE_RECTANGLE,
       .rectangle = {playerStartPosition.x, playerStartPosition.y, player.size.x, player.size.y},
   };

   player.object.color = BLUE;

   InitGameObject(&player.object, playerShape, player.object.color, OBJECT_TYPE_COLLIDEABLE, "P1");

   // Movement properties
   player.velocity = (Vector2){0.0f, 0.0f};
   player.terminal_velocity = (Vector2){50.0f, 15.0f}; // x term vel is placeholder for now
   player.sprint_speed_mod = 2.0f;
   player.sneak_speed_mod = 0.5f;

   // Jumping mechanics
   player.grounded = GROUNDED_STATE_UNGROUNDED;
   player.gravity = 0.5f;
   player.jump_speed = 12.0f;
   player.max_jump_height = player.size.y * 2;
   player.max_jumps = 2;
   player.remaining_jumps = player.max_jumps;
}

void UpdatePlayer(void)
{
   // Player rect object alias
   Rectangle *playerRect = &player.object.shape.rectangle;

   playerCenter = (Vector2){playerRect->x + (playerRect->width / 2.0f),
                            playerRect->y + (playerRect->height / 2.0f)};

   // Update player corners
   UpdateGameObject(&player.object);

   // Control grounded state properly based on player bottom - floor top collision
   if (player.bottomCollide)
   {
      player.grounded = GROUNDED_STATE_GROUNDED;
   }
   else
   {
      player.grounded = GROUNDED_STATE_UNGROUNDED;
   }

   // Reapply some states based on grounding
   if (player.grounded == GROUNDED_STATE_GROUNDED)
   {
      // LogMessage(LOG_DEBUG, "player grounded");
      player.remaining_jumps = player.max_jumps;
      player.velocity.y = 0.0f;
   }
   else
   {
      // LogMessage(LOG_DEBUG, "player ungrounded");
      // Apply gravity and terminal y velocity
      if (player.velocity.y < player.terminal_velocity.y)
      {
         player.velocity.y += player.gravity;
      }
      else
      {
         player.velocity.y = player.terminal_velocity.y;
      }

      // Apply vertical movement
      playerRect->y += player.velocity.y;
   }

   // Check for ceiling collision
   if (playerRect->y <= 0)
   {
      playerRect->y = 0;
      player.velocity.y = 0.0f;

      LogMessage(LOG_DEBUG, "Player top collided with the ceiling");
   }

   // Horizontal movement controls
   player.move_speed = 3.5f; // Reset move speed every frame

   // Sprint/sneaking modifiers
   if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
      player.move_speed *= player.sprint_speed_mod;

   // if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))
   //    player.move_speed *= player.sneak_speed_mod;

   if (IsKeyDown(KEY_RIGHT))
      player.velocity.x = player.move_speed;

   if (IsKeyDown(KEY_LEFT))
      player.velocity.x = -(player.move_speed);

   if (!IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT))
      player.velocity.x = 0.0f;

   // Apply horizontal movement
   playerRect->x += player.velocity.x;

   // God mode debug controls (also set gravity to 0)
   // if (IsKeyDown(KEY_UP))
   //    player.velocity.y = -(player.move_speed);

   // if (IsKeyDown(KEY_DOWN))
   //    player.velocity.y = player.move_speed;

   // if (!IsKeyDown(KEY_UP) && !IsKeyDown(KEY_DOWN))
   //    player.velocity.y = 0.0f;

   // Apply vertical movement
   // playerRect->y += player.velocity.y;

   // Jump logic
   if (IsKeyPressed(KEY_SPACE) && player.remaining_jumps > 0)
   {
      player.grounded = GROUNDED_STATE_UNGROUNDED;
      player.velocity.y = -(player.jump_speed);
      player.remaining_jumps--;

      LogMessage(LOG_DEBUG, "Player jumped, {%d} remaining jumps", player.remaining_jumps);
   }

   // Reset player
   if ((IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_R)) || (player.object.shape.rectangle.y >= SCREEN_DIMENSIONS.y * 2.0f))
   {
      player.object.shape.rectangle.x = SCREEN_DIMENSIONS.x / 2.0f;
      player.object.shape.rectangle.y = SCREEN_DIMENSIONS.y - player.size.y - 100.0f;
      player.grounded = GROUNDED_STATE_UNGROUNDED;
   }

   // Emit player particles
   if (player.velocity.x != 0 || player.velocity.y != 0)
   {
      EmitPlayerParticles(playerCenter, 500, GetComplimentaryColor(player.object.color));
   }
}

void DrawPlayer(void)
{
   // Object
   DrawGameObject(&player.object);

   // Additional info for debugging
   // int textWidth = MeasureText(TextFormat("Position: %.0fx%.0f", SCREEN_DIMENSIONS.x, SCREEN_DIMENSIONS.y), 20);
   // DrawText(
   //     TextFormat(
   //         "Position: %.0fx%.0f\nWall Offsets: %.2f - %.2f\nVelocity: %.2fx%.2f\n%s\nJumps: %d",
   //         player.object.shape.rectangle.x, player.object.shape.rectangle.y,
   //         0 + player.object.shape.rectangle.x,
   //         SCREEN_DIMENSIONS.x - player.object.shape.rectangle.x,
   //         player.velocity.x,
   //         player.velocity.y,
   //         player.grounded > 0 ? "GROUNDED" : "UNGROUNDED",
   //         player.remaining_jumps),
   //     SCREEN_DIMENSIONS.x / 2 - textWidth / 2,
   //     10,
   //     20,
   //     BLACK);
}

/**
 * @brief Get the Player object memory address
 * @return Player* object
 */
Player *GetPlayer(void)
{
   return &player;
}

/**
 * @brief Free dynamically allocated memory for the player's object label
 * @return void - Works on internal Player object
 */
void CleanUpPlayer(void)
{
   if (player.object.label)
   {
      free(player.object.label);
   }
}