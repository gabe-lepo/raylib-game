#ifndef FLOOR_H
#define FLOOR_H

#include "objects.h"
#include "game/screen.h"

#include <stddef.h>

#define MIN_FLOOR_WIDTH 100
#define MAX_FLOOR_WIDTH 300
#define FLOOR_HEIGHT 20

void InitFloors(GameObject *floors, size_t floorCount, unsigned int seed);
void DrawFloors(GameObject *floors, size_t floorCount);
// GameObject *getFloors(size_t *count);

#endif