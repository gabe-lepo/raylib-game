#ifndef FLOOR_H
#define FLOOR_H

#include "objects.h"
#include "game/screen.h"

#include <stddef.h>

#define MAX_FLOORS 10
#define MIN_FLOOR_WIDTH 100
#define MAX_FLOOR_WIDTH 300
#define FLOOR_HEIGHT 20

void InitFloors(unsigned int seed);
void DrawFloors(void);
GameObject *getFloors(size_t *count);

#endif