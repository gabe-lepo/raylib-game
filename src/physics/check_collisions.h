#ifndef CHECK_COLLISIONS_H
#define CHECK_COLLISIONS_H

#include "raylib.h"
#include "objects/player.h"
#include "objects/floor.h"
#include "objects/screen_chunks.h"

#include <stddef.h>

void CheckPlayerFloorCollision(Player *player, Floor objects[], size_t floorCount);
void CheckPlayerChunkCollision(Player *player, Chunk chunks[], size_t chunkCount);

#endif