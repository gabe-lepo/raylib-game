#include "objects.h"
#include "floor.h"
#include "screen.h"

static GameObject floor;

void InitFloor(void)
{
   Vector2 floorPosition = {0, SCREEN_HEIGHT - 50};
   Vector2 floorSize = {SCREEN_WIDTH, 50};
   InitGameObject(&floor, floorPosition, floorSize, BLACK, OBJECT_TYPE_COLLIDEABLE);
}

void DrawFloor(void)
{
   DrawGameObject(&floor);
}

GameObject *getFloor(void)
{
   return &floor;
}