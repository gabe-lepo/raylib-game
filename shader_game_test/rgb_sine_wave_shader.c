#include "raylib.h"

#include <stdio.h>

// Inline fragment shader (use raylib default vertext shader)
const char *fragmentShaderCode_sineWave =
    "#version 330\n"
    "uniform float u_time;\n"
    "out vec4 fragColor;\n"
    "float screenHeight = 450.0f;\n"
    "float placementOffset = screenHeight * 0.5;\n"
    "float frequency = 0.05;\n"
    "float amplitude = screenHeight * 0.33;\n"
    "float offset = 40.0;\n"
    "void main(){\n"
    "float particleOffset = offset;\n"
    "float red_wave = sin(gl_FragCoord.x * (frequency * 0.1) + u_time + particleOffset) * amplitude + placementOffset;\n"
    "float red_intensity = smoothstep(1.5, 0.0, abs(gl_FragCoord.y - red_wave) - 10.0);\n"
    "particleOffset += offset;\n"
    "float green_wave = sin(gl_FragCoord.x * (frequency * 0.33) + u_time + particleOffset) * amplitude + placementOffset;\n"
    "float green_intensity = smoothstep(1.5, 0.0, abs(gl_FragCoord.y - green_wave) - 10.0);\n"
    "particleOffset += offset;\n"
    "float blue_wave = sin(gl_FragCoord.x * (frequency * 1.0) + u_time + particleOffset) * amplitude + placementOffset;\n"
    "float blue_intensity = smoothstep(1.5, 0.0, abs(gl_FragCoord.y - blue_wave) - 10.0);\n"
    "float alpha_intensity = sin(u_time) * 0.5 + 0.5;\n"
    "fragColor = vec4(red_intensity, green_intensity, blue_intensity, 1.0);\n"
    "}\n";

int main(void)
{
   // Consts
   const Vector2 SCREEN_DIMENSIONS = (Vector2){800.0f, 450.0f};

   // Creates OpenGL context to LoadShader
   InitWindow(SCREEN_DIMENSIONS.x, SCREEN_DIMENSIONS.y, "RGB Sine Wave Shader");

   // Shader struct setup
   Shader shader = LoadShaderFromMemory(0, fragmentShaderCode_sineWave); // Default raylib vertext shader
   if (shader.id == 0)
   {
      printf("[FATAL]: Shader failed to load\n");
      CloseWindow();
      return 1;
   }
   else if (!IsShaderValid(shader))
   {
      printf("[FATAL]: Shader not valid\n");
      CloseWindow();
      return 1;
   }
   else
   {
      printf("[INFO]: Shader loaded successfully\n");
   }

   // Shader vars
   int fd_u_time = GetShaderLocation(shader, "u_time");
   float ShaderTime = 0.0f;
   float *p_ShaderTime = &ShaderTime;

   // Other setup stuff
   // SetTargetFPS(60);
   Rectangle fullscreenMask = {0, 0, SCREEN_DIMENSIONS.x, SCREEN_DIMENSIONS.y};

   while (!WindowShouldClose())
   {
      ShaderTime += GetFrameTime();
      SetShaderValue(shader, fd_u_time, p_ShaderTime, SHADER_UNIFORM_FLOAT);

      BeginDrawing();
      ClearBackground(BLACK);

      BeginShaderMode(shader);
      DrawRectangleRec(fullscreenMask, BLACK);
      EndShaderMode();

      // DrawFPS(10, 10);

      EndDrawing();
   }

   UnloadShader(shader);
   CloseWindow();

   return 0;
}