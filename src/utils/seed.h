#ifndef SEED_H
#define SEED_H

#include "raylib.h"

void InitSeed(unsigned int value);
unsigned int GetSeed(void);
void RandomizeSeed(bool init);

#endif