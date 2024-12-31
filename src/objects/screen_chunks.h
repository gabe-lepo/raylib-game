#ifndef SCREEN_CHUNKS_H
#define SCREEN_CHUNKS_H

#include "raylib.h"
#include "objects.h"

typedef struct Chunk
{
   GameObject object;
} Chunk;

void InitChunks(void);
void UpdateChunks(void);
void DrawChunks(void);
Chunk *GetChunks(int *countChunks, int *xCount, int *yCount);
void CleanUpChunks(void);

#endif