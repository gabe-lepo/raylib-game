#include "shader.h"
#include "logging/log.h"
#include "game/backgrounds/shaded_background.h"
#include "game/screen.h"
#include "objects/player.h"

#include <stdlib.h>
#include <math.h>

static Shader shader;
static int u_time_location;
static float ShaderTime;
static float oscillationSpeedMod;

const char *fs_file = "/Users/glepoutre/Documents/vscode/raylib-game/src/shaders/fragment/rgb_sine_wave.fs";

int InitShader(void)
{
   // Default vertext shader, inline fragment shader
   shader = LoadShader(0, fs_file);
   if (shader.id == 0)
   {
      LogMessage(LOG_ERROR, "Shader failed to load");
      return EXIT_FAILURE;
   }
   else if (!IsShaderValid(shader))
   {
      LogMessage(LOG_ERROR, "Shader not valid");
      return EXIT_FAILURE;
   }
   else
   {
      LogMessage(LOG_INFO, "Shader loaded successfully!");
   }

   u_time_location = GetShaderLocation(shader, "u_time");
   ShaderTime = 0.0f;
   oscillationSpeedMod = 2.0f;

   SetShaderValue(shader, GetShaderLocation(shader, "u_screenHeight"), &SCREEN_DIMENSIONS.y, SHADER_UNIFORM_FLOAT);

   InitShadedBackground();

   return EXIT_SUCCESS;
}

void UpdateShader(void)
{
   ShaderTime += GetFrameTime() * oscillationSpeedMod;
   SetShaderValue(shader, u_time_location, &ShaderTime, SHADER_UNIFORM_FLOAT);

   UpdateShadedBackground();
}

void DrawShader(void)
{
   BeginShaderMode(shader);
   DrawShadedBackground();
   EndShaderMode();
}

void CleanupShader(void)
{
   UnloadShader(shader);
}

Shader *GetShader(void)
{
   return &shader;
}
