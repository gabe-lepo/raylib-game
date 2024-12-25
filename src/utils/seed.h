#ifndef SEED_H
#define SEED_H

#include "raylib.h"

typedef struct RandomSeed
{
   unsigned int value;
} RandomSeed;

void setSeed(int value);
RandomSeed getSeed(void);

#endif