#include "floor.h"
#include "logging/log.h"
#include "utils/color_utils.h"
#include "game/screen.h"

#include <stdlib.h>

static Floor floors[8];
static int floorCount = sizeof(floors) / sizeof(floors[0]);

/**
 * @brief Initialize random array of floors.
 * @return void - Operates on internal Floor object array.
 * @note To get truely random floor placement, you MUST call raylib's SetRandomSeed() first; use src/utils/seed.*.
 */
void InitFloors(void)
{
   for (size_t i = 0; i < floorCount; i++)
   {
      // Since we're using Vector2 for min/max limits, x is the min; y is the max.
      floors[i].width_limit = (Vector2){100, 300};
      floors[i].height_limit = (Vector2){20, 20};

      // Random dimensions within limits
      float width = (float)GetRandomValue((int)floors[i].width_limit.x, (int)floors[i].width_limit.x);
      float height = (float)GetRandomValue((int)floors[i].height_limit.x, (int)floors[i].height_limit.x);

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
      InitGameObject(&floors[i].object, floorShape, color, OBJECT_TYPE_COLLIDEABLE, TextFormat("Floor %zu", i));
   }
}

/**
 * @brief Doesn't do anything at the moment.
 * @return void - Operates on internal Floor object array.
 */
void UpdateFloors(void)
{
   // TODO
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