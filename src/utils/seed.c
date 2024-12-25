#include "seed.h"

#include <time.h>

RandomSeed gameSeed;

void InitSeed(void)
{
   // Use current time for initial random seed
   gameSeed.value = (unsigned int)time(NULL);
}

void setSeed(int value)
{
   if (value < 0)
   {
      // TODO
   }
   else
   {
      SetRandomSeed((unsigned int)value);
   }
}

RandomSeed getSeed(void)
{
   return gameSeed;
}