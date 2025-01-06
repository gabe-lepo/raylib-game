#include "shader.h"
#include "logging/log.h"
#include "game/backgrounds/shaded_background.h"
#include "game/screen.h"
#include "objects/player.h"

#include <stdlib.h>
#include <math.h>

static Shader shader;
static float ShaderTime;

const char *fs_file = "src/shaders/fragment/blue_gold_pulse.fs";

int InitShader(void)
{
   // Default raylib vs
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

   SetShaderValue(shader, GetShaderLocation(shader, "u_screenX"), &SCREEN_DIMENSIONS.x, SHADER_UNIFORM_FLOAT);
   SetShaderValue(shader, GetShaderLocation(shader, "u_screenY"), &SCREEN_DIMENSIONS.y, SHADER_UNIFORM_FLOAT);
   ShaderTime = 0.0f;
   SetShaderValue(shader, GetShaderLocation(shader, "u_time"), &ShaderTime, SHADER_UNIFORM_FLOAT);

   InitShadedBackground();

   return EXIT_SUCCESS;
}

void UpdateShader(void)
{
   ShaderTime += GetFrameTime();
   SetShaderValue(shader, GetShaderLocation(shader, "u_time"), &ShaderTime, SHADER_UNIFORM_FLOAT);

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
