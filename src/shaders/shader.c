#include "shader.h"
#include "logging/log.h"
#include "objects/player.h"
#include "objects/floor.h"

#include <stdlib.h>

static const char *fragmentShaderCode_sinewave =
    "#version 330\n"

    "uniform float u_time;\n"
    "out vec4 fragColor;\n"

    "float screenHeight = 450.0;\n"
    "float yOffset = screenHeight * 0.5;\n"
    "float amplitude = screenHeight * 0.45;\n"
    "float frequency = 0.05;\n"
    "float lineThickness = 20.0;\n"

    "void main(){\n"
    "    float red_wave = sin(gl_FragCoord.x * (frequency * 0.1) + u_time) * amplitude + yOffset;\n"
    "    float red = smoothstep(1.0, 0.0, abs(gl_FragCoord.y - red_wave) - lineThickness);\n"

    "    float green_wave = sin(gl_FragCoord.x * (frequency * 0.33) + u_time) * amplitude + yOffset;\n"
    "    float green = smoothstep(1.0, 0.0, abs(gl_FragCoord.y - green_wave) - lineThickness);\n"

    "    float blue_wave = sin(gl_FragCoord.x * (frequency * 1.0) + u_time) * amplitude + yOffset;\n"
    "    float blue = smoothstep(1.0, 0.0, abs(gl_FragCoord.y - blue_wave) - lineThickness);\n"

    "    fragColor = vec4(red, green, blue, 1.0);\n"
    "}\n";

static Shader shader;
static int u_time_location;
static float ShaderTime;
static float *p_ShaderTime;
static float oscillationSpeedMod;

int InitShader(void)
{
   // Default vertext shader, inline fragment shader
   shader = LoadShaderFromMemory(0, fragmentShaderCode_sinewave);
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
   p_ShaderTime = &ShaderTime;
   oscillationSpeedMod = 2.0f;

   return EXIT_SUCCESS;
}

void UpdateShader(void)
{
   ShaderTime += GetFrameTime() * oscillationSpeedMod;
   SetShaderValue(shader, u_time_location, p_ShaderTime, SHADER_UNIFORM_FLOAT);
}

void DrawShader(void)
{
   BeginShaderMode(shader);
   DrawFloors();
   DrawPlayer();
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
