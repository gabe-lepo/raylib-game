#include "lerp.h"

// Linear interpolation (i.e. for smooth movement)
float MyLerp(float current, float target, float delta)
{
   // Clamp delta input
   if (delta < 0.0f)
   {
      delta = 0.0f;
   }
   if (delta > 1.0f)
   {
      delta = 1.0f;
   }

   // Return to be used recursively until current == target
   return current + (target - current) * delta;
}