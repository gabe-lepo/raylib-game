#include "particle.h"
#include "logging/log.h"

static ParticleSystem particleSystem = {0};

int InitParticleSystem(size_t maxCount)
{
   particleSystem.particles = (Particle *)malloc(maxCount * sizeof(Particle));
   if (!particleSystem.particles)
   {
      LogMessage(LOG_ERROR, "ParticleSystem: Failed to allocate memory for particles");
      return EXIT_FAILURE;
   }

   particleSystem.count = 0;
   particleSystem.maxCount = maxCount;
   LogMessage(LOG_INFO, "ParticleSystem: Initialized with maxCount {%zu}", maxCount);
   return EXIT_SUCCESS;
}

/**
 * @brief Add a Particle object to the ParticleSystem
 *
 * @todo this function is called way too many times, need to limit it, hence the first if check
 *
 * @param position Vector of particle
 * @param velocity How it should move
 * @param radius Size of particle
 * @param color Color of particle
 * @param lifespan Overall time span of it existing
 * @param decayRate How quickly does it reach lifespan limit
 */
void AddParticleToSystem(Vector2 position, Vector2 velocity, float radius, Color color, float lifespan, float decayRate)
{
   if (particleSystem.count >= particleSystem.maxCount)
   {
      particleSystem.count = particleSystem.maxCount;
      // LogMessage(LOG_WARNING, "Tried to add too many particles to system!");
      return;
   }

   Particle *particle = &particleSystem.particles[particleSystem.count++];
   particle->position = position;
   particle->velocity = velocity;
   particle->radius = radius;
   particle->color = color;
   particle->lifespan = lifespan;
   particle->decayRate = decayRate;

   // LogMessage(LOG_INFO, "ParticleSystem: Added particle at position {%.2fx%.2f}", position.x, position.y);
}

void UpdateParticleSystem(float deltaTime)
{
   size_t activeCount = 0;

   for (size_t i = 0; i < particleSystem.count; i++)
   {
      Particle *particle = &particleSystem.particles[i];

      particle->position.x += particle->velocity.x * deltaTime;
      particle->position.y += particle->velocity.y * deltaTime;
      particle->lifespan -= particle->decayRate * deltaTime;

      if (particle->lifespan > 0.0f)
      {
         if (activeCount != i)
         {
            particleSystem.particles[activeCount] = *particle;
         }
         activeCount++;
      }
   }

   particleSystem.count = activeCount;
}

void DrawParticleSystem(void)
{
   for (size_t i = 0; i < particleSystem.count; i++)
   {
      Particle *particle = &particleSystem.particles[i];
      DrawCircleV(particle->position, particle->radius, Fade(particle->color, particle->lifespan));
   }
}

ParticleSystem *GetParticleSystem(void)
{
   return &particleSystem;
}

void CleanupParticleSystem(void)
{
   if (particleSystem.particles)
   {
      free(particleSystem.particles);
      particleSystem.particles = NULL;
   }
   else
   {
      LogMessage(LOG_WARNING, "ParticleSystem: No particles to clean!");
   }

   particleSystem.count = 0;
   particleSystem.maxCount = 0;
   LogMessage(LOG_INFO, "ParticleSystem: Cleaned particles!");
}
