#ifndef SHADER_H
#define SHADER_H

#include "raylib.h"

int InitShader(void);
void UpdateShader(void);
void DrawShader(void);
void CleanupShader(void);
Shader *GetShader(void);

#endif