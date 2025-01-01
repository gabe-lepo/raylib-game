#include "seed.h"
#include "logging/log.h"

#include <time.h>
#include <stdlib.h>

static unsigned int gameSeed;

/**
 * @brief Initialize random seed for other RNG actions
 * @param value The seed value to use, 0 for a time-based seed
 * @return void - Sets game seed via SetRandomSeed()
 */
void InitSeed(unsigned int value)
{
   if (value)
   {
      gameSeed = value;
   }
   else
   {
      gameSeed = (unsigned int)time(NULL);
   }

   SetRandomSeed(gameSeed);

   LogMessage(LOG_INFO, "RNG seed initialized as {%d}", GetSeed());
}

/**
 * @brief Get the game seed value
 * @return unsigned int gameSeed
 */
unsigned int GetSeed(void)
{
   return gameSeed;
}

/**
 * @brief Set stdlib rand seed as game seed, reset game seed to rand()
 * @param init Boolean to initialize raylib seed with the new game seed
 * @return void - randomizes game seed, use GetSeed() to see changes
 */
void RandomizeSeed(bool init)
{
   srand(gameSeed);
   gameSeed = (unsigned int)rand();

   if (init)
      InitSeed(gameSeed);
}