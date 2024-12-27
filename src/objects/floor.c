#include "floor.h"
#include "logging/log.h"
#include "utils/color_utils.h"

void InitFloors(GameObject *floors, size_t floorCount, unsigned int seed)
{
   LogMessage(LOG_INFO, "Initializing floors {[%zu]}:", floorCount);
   // SetRandomSeed(seed);
   int colorRandMin = 0;
   int colorRandMax = 255;

   for (size_t i = 0; i < floorCount; i++)
   {
      // Random dimensions and positions
      float width = (float)GetRandomValue(MIN_FLOOR_WIDTH, MAX_FLOOR_WIDTH);
      float x = (float)GetRandomValue(0, SCREEN_DIMENSIONS.x - (int)width);
      float y = (float)GetRandomValue(FLOOR_HEIGHT, SCREEN_DIMENSIONS.y - FLOOR_HEIGHT * 2);

      Vector2 size = {width, FLOOR_HEIGHT};
      Vector2 position = {x, y};

      // Unique colors
      Color color = GetRandomColor(0, 255, 255);

      // Init the floor
      InitGameObject(&floors[i], position, size, color, OBJECT_TYPE_COLLIDEABLE, TextFormat("Floor %zu", i));
   }
   LogMessage(LOG_INFO, "Done initializing floors\n");
}

void DrawFloors(GameObject *floors, size_t floorCount)
{
   for (size_t i = 0; i < floorCount; i++)
   {
      DrawGameObject(&floors[i]);
   }
}

// GameObject *getFloors(size_t *count)
// {
//    *count = floorCount;
//    return floors;
// }