#ifndef BACKGROUND_SHADER_H
#define BACKGROUND_SHADER_H

#include "raylib.h"
#include "raymath.h" // Must be defined here, directly after raylib otherwise Vector2 definitions collides

int InitShader(void);
void UpdateShader(void);
void DrawShader(void);
void CleanupShader(void);
Shader *GetShader(void);

#endif