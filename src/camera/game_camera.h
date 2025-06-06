#ifndef GAME_CAMERA_H
#define GAME_CAMERA_H

#include "raylib.h"
#include "raymath.h"
#include "objects/player.h"

#include <math.h>

typedef struct GameCamera
{
   Camera2D camera2d;
} GameCamera;

void InitGameCamera(Player *player);
void UpdateGameCamera(Player *player);
GameCamera *GetGameCamera(void);
void CleanUpGameCamera(void);

void CenterGameCamera(void);

#endif