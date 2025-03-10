#ifndef PARALLAX_BACKGROUND_H
#define PARALLAX_BACKGROUND_H

#include "raylib.h"

typedef struct ParallaxLayer
{
   Texture2D texture;
   float speed;
   float offsetX;
} ParallaxLayer;

void InitParallaxBackground(void);
void UpdateParallaxBackground(float playerSpeed);
void DrawParallaxBackground(void);
void CleanupParallaxBackground(void);

#endif