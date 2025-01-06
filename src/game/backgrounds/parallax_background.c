#include "parallax_background.h"

#define NUM_LAYERS 3

static ParallaxLayer layers[NUM_LAYERS];

void InitParallaxBackground(void)
{
   layers[0].texture = LoadTexture("/Users/glepoutre/Documents/vscode/raylib-game/assets/textures/layer0.png");
   layers[0].speed = 0.2f;

   layers[1].texture = LoadTexture("/Users/glepoutre/Documents/vscode/raylib-game/assets/textures/layer1.png");
   layers[1].speed = 0.5f;

   layers[2].texture = LoadTexture("/Users/glepoutre/Documents/vscode/raylib-game/assets/textures/layer2.png");
   layers[2].speed = 0.8f;

   for (int i = 0; i < NUM_LAYERS; i++)
      layers[i].offsetX = 0;
}

void UpdateParallaxBackground(float playerSpeed)
{
   for (int i = 0; i < NUM_LAYERS; i++)
   {
      layers[i].offsetX -= playerSpeed * layers[i].speed;
      if (layers[i].offsetX <= -layers[i].texture.width)
         layers[i].offsetX += layers[i].texture.width;
   }
}

void DrawParallaxBackground(void)
{
   for (int i = 0; i < NUM_LAYERS; i++)
   {
      DrawTextureEx(layers[i].texture, (Vector2){layers[i].offsetX, 0}, 0.0f, 1.0f, WHITE);
      DrawTextureEx(layers[i].texture, (Vector2){layers[i].offsetX + layers[i].texture.width, 0}, 0.0f, 1.0f, WHITE);
   }
}

void CleanupParallaxBackground(void)
{
   for (int i = 0; i < NUM_LAYERS; i++)
      UnloadTexture(layers[i].texture);
}
