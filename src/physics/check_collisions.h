#ifndef CHECK_COLLISIONS_H
#define CHECK_COLLISIONS_H

#include "raylib.h"
#include "objects/player.h"
#include "objects/floor.h"

#include <stddef.h>

void CheckPlayerFloorCollision(Player *player, Floor objects[], size_t floorCount);

#endif