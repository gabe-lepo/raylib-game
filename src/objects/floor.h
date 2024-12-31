#ifndef FLOOR_H
#define FLOOR_H

#include "objects.h"

typedef struct Floor
{
   // Object
   GameObject object;

   // Size constraints
   Vector2 width_limit;
   Vector2 height_limit;

   // Other
} Floor;

void InitFloors(void);
void UpdateFloors(void);
void DrawFloors(void);
Floor *GetFloors(int *countFloors);
void CleanUpFloors(void);

#endif