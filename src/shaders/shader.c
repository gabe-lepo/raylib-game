#include "shader.h"

#include "logging/log.h"

Shader shader;
float ShaderTime = 0.0f; // DO NOT CALL this "time", causes weird bus errors on m1 macOS

void InitShader(void)
{
   LogMessage(LOG_INFO, "Initializing shaders");
   shader = LoadShader("shaders/basic.vs", "shaders/basic.fs");
   SetShaderValue(shader, GetShaderLocation(shader, "texture0"), (int[]){0}, SHADER_UNIFORM_INT);
}

void UpdateShader(void)
{
   ShaderTime += GetFrameTime();
   SetShaderValue(shader, GetShaderLocation(shader, "ShaderTime"), &ShaderTime, SHADER_UNIFORM_FLOAT);
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