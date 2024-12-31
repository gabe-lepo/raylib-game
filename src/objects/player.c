#include "player.h"
#include "logging/log.h"

#include <stdlib.h>
#include <string.h>

static Player player;

void InitPlayer(void)
{
   // Init player as 50x50 px rectangle
   player.size = (Vector2){50.0f, 50.0f};
   Vector2 playerStartPosition = {SCREEN_DIMENSIONS.x / 2, (float)SCREEN_DIMENSIONS.y - player.size.y - 100};

   Shape playerShape = {
       .type = SHAPE_TYPE_RECTANGLE,
       .rectangle = {playerStartPosition.x, playerStartPosition.y, player.size.x, player.size.y},
   };

   player.object.color = BLUE;

   InitGameObject(&player.object, playerShape, player.object.color, OBJECT_TYPE_COLLIDEABLE, "Player");

   // Movement properties
   player.velocity = (Vector2){0.0f, 0.0f};
   player.terminal_velocity = (Vector2){50.0f, 30.0f}; // x term vel is placeholder for now
   player.move_speed = 5.0f;
   player.sprint_speed_mod = 2.0f;
   player.sneak_speed_mod = 0.5f;

   // Jumping mechanics
   player.grounded = GROUNDED_STATE_UNGROUNDED;
   player.gravity = 0.5f;
   player.jump_speed = (15.0f <= player.terminal_velocity.y) ? 15.0f : player.terminal_velocity.y; // Ensure jump speed doesn't exceed y term vel
   player.max_jump_height = player.size.y * 2;
   player.max_jumps = 2;
   player.remaining_jumps = player.max_jumps;
}

void UpdatePlayer(void)
{
   // Player rect object alias
   Rectangle *playerRect = &player.object.shape.rectangle;

   // Reapply some states based on grounding
   if (player.grounded == GROUNDED_STATE_GROUNDED)
   {
      player.remaining_jumps = player.max_jumps;
      player.velocity.y = 0.0f;
   }
   else
   {
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

   // Check for ground collision at bottom of screen
   if (playerRect->y + playerRect->height > SCREEN_DIMENSIONS.y)
   {
      playerRect->y = SCREEN_DIMENSIONS.y - playerRect->height;
      player.velocity.y = 0.0f;
      player.grounded = GROUNDED_STATE_GROUNDED;
      player.remaining_jumps = player.max_jumps;
      LogMessage(LOG_DEBUG, "Player grounded due to collision at bottom of screen");
   }

   // Check for ceiling collision
   if (playerRect->y <= 0)
   {
      playerRect->y = 0;
      player.velocity.y = 0.0f;

      LogMessage(LOG_DEBUG, "Player hit the ceiling");
   }

   // Horizontal movement controls
   player.move_speed = 5.0f; // Reset move speed every frame

   // Sprint/sneaking modifiers
   if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
      player.move_speed *= player.sprint_speed_mod;

   if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))
      player.move_speed *= player.sneak_speed_mod;

   if (IsKeyDown(KEY_RIGHT))
   {
      player.velocity.x = player.move_speed;
      // LogMessage(LOG_DEBUG, "Player moving right with velocity {%.0f}", player.velocity.x);
   }

   if (IsKeyDown(KEY_LEFT))
   {
      player.velocity.x = -(player.move_speed);
      // LogMessage(LOG_DEBUG, "Player moving left with velocity {%.0f}", player.velocity.x);
   }

   if (!IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT))
      player.velocity.x = 0.0f;

   // Apply horizontal movement
   playerRect->x += player.velocity.x;

   // Horizontal screen collision (must be done after horizontal movement checks)
   if (playerRect->x + playerRect->width >= SCREEN_DIMENSIONS.x)
   {
      playerRect->x = SCREEN_DIMENSIONS.x - playerRect->width - SCREEN_EDGE_PADDING;
   }
   if (playerRect->x <= 0)
   {
      playerRect->x = SCREEN_EDGE_PADDING;
   }

   // Jump logic
   if (IsKeyPressed(KEY_SPACE) && player.remaining_jumps > 0)
   {
      player.grounded = GROUNDED_STATE_UNGROUNDED;
      player.velocity.y = -(player.jump_speed);
      player.remaining_jumps--;

      LogMessage(LOG_DEBUG, "Player jumped, {%d} remaining jumps", player.remaining_jumps);
   }
}

void DrawPlayer(void)
{
   // Object
   DrawGameObject(&player.object);

   // Additional info for debugging
   int textWidth = MeasureText(TextFormat("Position: %.0fx%.0f", SCREEN_DIMENSIONS.x, SCREEN_DIMENSIONS.y), 20);
   DrawText(
       TextFormat(
           "Position: %.0fx%.0f\nWall Offsets: %.2f - %.2f\nVelocity: %.2fx%.2f\n%s\nJumps: %d",
           player.object.shape.rectangle.x, player.object.shape.rectangle.y,
           0 + player.object.shape.rectangle.x,
           SCREEN_DIMENSIONS.x - player.object.shape.rectangle.x,
           player.velocity.x,
           player.velocity.y,
           player.grounded > 0 ? "GROUNDED" : "UNGROUNDED",
           player.remaining_jumps),
       SCREEN_DIMENSIONS.x / 2 - textWidth / 2,
       10,
       20,
       BLACK);

   DrawText(
       TextFormat(
           "BLx {%.0f} | BRx {%.0f}",
           player.object.shape.rectangle.x,
           player.object.shape.rectangle.x + player.object.shape.rectangle.width),
       100, 100,
       20, BLACK);
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