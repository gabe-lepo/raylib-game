#include "objects.h"
#include "floor.h"
#include "screen.h"

static GameObject floor;

void InitFloor(void)
{
   float offsetX = 40.0f;
   Vector2 topLeft = {0 + offsetX, SCREEN_HEIGHT - offsetX};
   Vector2 size = {SCREEN_WIDTH - offsetX * 2, offsetX / 2};
   InitGameObject(&floor, topLeft, size, BLACK, OBJECT_TYPE_COLLIDEABLE);
}

void DrawFloor(void)
{
   DrawGameObject(&floor);
}

GameObject *getFloor(void)
{
   return &floor;
}