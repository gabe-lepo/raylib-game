#include "shader.h"

Shader shader;
float time = 0.0f;

void InitShader(void)
{
   shader = LoadShader("shaders/basic.vs", "shaders/basic.fs");
   SetShaderValue(shader, GetShaderLocation(shader, "texture0"), (int[]){0}, SHADER_UNIFORM_INT);
}

void UpdateShader(void)
{
   time += GetFrameTime();
   SetShaderValue(shader, GetShaderLocation(shader, "time"), &time, SHADER_UNIFORM_FLOAT);
}

void DrawShader(void)
{
   // TODO
}

void CleanupShader(void)
{
   UnloadShader(shader);
}

Shader *GetShader(void)
{
   return &shader;
}