#ifndef PARTICLE_H
#define PARTICLE_H

#include "raylib.h"

#include <stdlib.h>

typedef struct Particle
{
   // Positioning
   Vector2 position;
   Vector2 velocity;
   float radius;

   // Visibility
   Color color;
   float lifespan;
   float decayRate;
} Particle;

typedef struct ParticleSystem
{
   Particle *particles;
   size_t count;
   size_t maxCount;
} ParticleSystem;

int InitParticleSystem(size_t maxCount);
void AddParticleToSystem(Vector2 position, Vector2 velocity, float radius, Color color, float lifespan, float decayRate);
void UpdateParticleSystem(float deltaTime);
void DrawParticleSystem(void);
ParticleSystem *GetParticleSystem(void);
void CleanupParticleSystem(void);

#endif