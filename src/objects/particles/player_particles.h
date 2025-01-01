#ifndef PLAYER_PARTICLES_H
#define PLAYER_PARTICLES_H

#include "raylib.h"

#include <stdlib.h>

int InitPlayerParticles(size_t maxParticles);
void EmitPlayerParticles(Vector2 playerPosition, size_t count, Color color);
void UpdatePlayerParticles(float deltaTime);
void DrawPlayerParticles(void);
void CleanupPlayerParticles(void);

#endif