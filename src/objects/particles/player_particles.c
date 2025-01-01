#include "player_particles.h"
#include "particle.h"
#include "logging/log.h"

#include <math.h>

int InitPlayerParticles(size_t maxParticles)
{
   if (InitParticleSystem(maxParticles) != EXIT_SUCCESS)
   {
      LogMessage(LOG_ERROR, "PlayerParticles: Failed to init particle system for player");
      return EXIT_FAILURE;
   }
   else
   {
      LogMessage(LOG_INFO, "PlayerParticles: Initialized player particles with max count {%zu}", maxParticles);
   }
}

void EmitPlayerParticles(Vector2 playerPosition, size_t count, Color color)
{
   for (size_t i = 0; i < count; i++)
   {
      // Random velocity
      float angle = GetRandomValue(0, 360) * (PI / 180.0f); // Degrees to radians
      float speed = (float)GetRandomValue(20, 60) / 10.0f;

      Vector2 velocity = {
          .x = cosf(angle) * speed,
          .y = sinf(angle) * speed};

      // Randomized life span and decay
      float lifespan = (float)GetRandomValue(50, 150) / 100.0f;
      float decayRate = (float)GetRandomValue(20, 50) / 100.0f;

      // Random size
      float radius = (float)GetRandomValue(2, 5);

      // Emit
      AddParticleToSystem(playerPosition, velocity, radius, color, lifespan, decayRate);
   }
}

void UpdatePlayerParticles(float deltaTime)
{
   UpdateParticleSystem(deltaTime);
}

void DrawPlayerParticles(void)
{
   DrawParticleSystem();
}

void CleanupPlayerParticles(void)
{
   CleanupParticleSystem();
}
