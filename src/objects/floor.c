#include "floor.h"
#include "logging/log.h"
#include "utils/color_utils.h"
#include "game/screen.h"

#include <stdlib.h>

static Floor floors[10];
static int floorCount = sizeof(floors) / sizeof(floors[0]);

/**
 * @brief Initialize random array of floors.
 * @return void - Operates on internal Floor object array.
 * @note To get truely random floor placement, you MUST call raylib's SetRandomSeed() first; use src/utils/seed.*.
 */
void InitFloors(void)
{
   // Randomly generate all but 2 of floor count, last 2 are for static wall and ground floors
   for (size_t i = 0; i < floorCount - 2; i++)
   {
      // Since we're using Vector2 for min/max limits, x is the min; y is the max.
      floors[i].width_limit = (Vector2){30.0f, 300.0f};
      floors[i].height_limit = (Vector2){20.0f, 80.0f};

      // Random dimensions within limits
      float width = (float)GetRandomValue((int)floors[i].width_limit.x, (int)floors[i].width_limit.y);
      float height = (float)GetRandomValue((int)floors[i].height_limit.x, (int)floors[i].height_limit.y);

      // Random positioning, ensuring within screen limits
      float x = (float)GetRandomValue(SCREEN_EDGE_PADDING, (int)(SCREEN_DIMENSIONS.x - width + SCREEN_EDGE_PADDING));
      float y = (float)GetRandomValue(SCREEN_EDGE_PADDING, (int)(SCREEN_DIMENSIONS.y - height + SCREEN_EDGE_PADDING));
      Vector2 position = {x, y};
      Vector2 size = {width, height};

      // Colors
      Color color = GetRandomColor(50, 200, 255);

      // Floor object shape
      Shape floorShape = {
          .type = SHAPE_TYPE_RECTANGLE,
          .rectangle = {position.x, position.y, size.x, size.y},
      };

      // Init the floor
      InitGameObject(&floors[i].object, floorShape, color, OBJECT_TYPE_COLLIDEABLE, TextFormat("F%zu", i));
   }

   // Generate the left screen boundary
   floors[floorCount - 2].width_limit = (Vector2){0, 0};
   floors[floorCount - 2].height_limit = (Vector2){0, 0};
   Shape floorShape = {
       .type = SHAPE_TYPE_RECTANGLE,
       .rectangle = {0, 0, 2, SCREEN_DIMENSIONS.y},
   };
   InitGameObject(&floors[floorCount - 2].object, floorShape, BLACK, OBJECT_TYPE_COLLIDEABLE, "Wall");

   // Generate the ground floor (moves horizontally with player)
   floors[floorCount - 1].width_limit = (Vector2){0, 0};
   floors[floorCount - 1].height_limit = (Vector2){0, 0};
   floorShape.rectangle = (Rectangle){0, SCREEN_DIMENSIONS.y, SCREEN_DIMENSIONS.x, 2};
   InitGameObject(&floors[floorCount - 1].object, floorShape, BLACK, OBJECT_TYPE_COLLIDEABLE, "Ground");
}

/**
 * @brief Call object updater for each floor
 * @return void - Operates on internal Floor object array.
 */
void UpdateFloors(Player *player)
{
   for (int i = 0; i < floorCount; i++)
   {
      UpdateGameObject(&floors[i].object);
   }

   // Move the ground floor with player to simulate infinite floor
   Floor *ground = &floors[floorCount - 1];
   ground->object.shape.rectangle.x = player->object.shape.rectangle.x - (SCREEN_DIMENSIONS.x / 2);
}

/**
 * @brief Draw the internal floor objects.
 * @return void - Operates on internal Floor object array.
 */
void DrawFloors(void)
{
   for (size_t i = 0; i < floorCount; i++)
   {
      DrawGameObject(&floors[i].object);
   }
}

/**
 * @brief Get the internal Floor object array.
 * @return Pointer to first Floor array item
 */
Floor *GetFloors(int *countFloors)
{

   *countFloors = floorCount; // Need this to pass floor pointer to check collision. Not very nice but it works
   return floors;             // Floors should be an array, so no need for "address of" operator...
}

/**
 * @brief Cleanup any dynamically allocated Floor memory.
 * @return void - Operates on internal Floor object array.
 */
void CleanUpFloors(void)
{
   for (size_t i = 0; i < floorCount; i++)
   {
      if (floors[i].object.label)
      {
         free(floors[i].object.label);
      }
   }
}