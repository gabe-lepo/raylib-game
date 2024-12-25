#ifndef FLOOR_H
#define FLOOR_H

#include "objects.h"
#include "game/screen.h"

#include <stddef.h>
#include <time.h>

#define MAX_FLOORS 10
#define MIN_FLOOR_WIDTH 100
#define MAX_FLOOR_WIDTH 300
#define FLOOR_HEIGHT 20

void InitFloors(void);
void DrawFloors(void);
GameObject *getFloors(size_t *count);

#endif