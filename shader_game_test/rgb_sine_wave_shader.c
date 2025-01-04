#include "raylib.h"

#include <stdio.h>

// Inline fragment shader (use raylib default vertext shader)
const char *fragmentShaderCode_sineWave =
    "#version 330\n"

    "uniform float u_time;\n"
    "out vec4 fragColor;\n"

    "float screenHeight = 900.0;\n"
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

int main(void)
{
   // Consts
   const Vector2 SCREEN_DIMENSIONS = (Vector2){1600.0f, 900.0f};

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
   float oscillationSpeedMod = 5.0f;

   // Other setup stuff
   // SetTargetFPS(60);
   Rectangle fullscreenMask = {0, 0, SCREEN_DIMENSIONS.x, SCREEN_DIMENSIONS.y};

   while (!WindowShouldClose())
   {
      ShaderTime += GetFrameTime() * oscillationSpeedMod;
      SetShaderValue(shader, fd_u_time, p_ShaderTime, SHADER_UNIFORM_FLOAT);

      BeginDrawing();
      ClearBackground(BLACK);

      BeginShaderMode(shader);
      DrawRectangleRec(fullscreenMask, BLACK);
      EndShaderMode();

      // Other non-shader draw tasks
      // Can't be drawn before or inside of ShaderMode block, not sure why!
      // DrawFPS(10, 10);

      EndDrawing();
   }

   UnloadShader(shader);
   CloseWindow();

   return 0;
}