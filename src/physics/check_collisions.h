#ifndef CHECK_COLLISIONS_H
#define CHECK_COLLISIONS_H

#include "raylib.h"
#include "objects/objects.h"
#include "objects/player.h"

#include <stddef.h>

void CheckPlayerCollision(Player *player, GameObject objects[], size_t objectCount);

#endif