#include "floor.h"

static GameObject floors[MAX_FLOORS];
static size_t floorCount = 0;

void InitFloors(void)
{
   SetRandomSeed((unsigned int)time(NULL));
   floorCount = MAX_FLOORS;
   int colorRandMin = 0;
   int colorRandMax = 255;

   for (size_t i = 0; i < floorCount; i++)
   {
      // Random dimensions and positions
      float width = (float)GetRandomValue(MIN_FLOOR_WIDTH, MAX_FLOOR_WIDTH);
      float x = (float)GetRandomValue(0, SCREEN_WIDTH - (int)width);
      float y = (float)GetRandomValue(FLOOR_HEIGHT, SCREEN_HEIGHT - FLOOR_HEIGHT * 2);

      Vector2 size = {width, FLOOR_HEIGHT};
      Vector2 position = {x, y};

      // Unique colors
      Color color = (Color){GetRandomValue(colorRandMin, colorRandMax), GetRandomValue(colorRandMin, colorRandMax), GetRandomValue(colorRandMin, colorRandMax), 255};

      // Init the floor
      InitGameObject(&floors[i], position, size, color, OBJECT_TYPE_COLLIDEABLE);
   }
}

void DrawFloors(void)
{
   for (size_t i = 0; i < floorCount; i++)
   {
      DrawGameObject(&floors[i]);
   }
}

GameObject *getFloors(size_t *count)
{
   *count = floorCount;
   return floors;
}