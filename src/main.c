#include "raylib.h"
#include "game/game.h"
#include "logging/log.h"
#include "camera/game_camera.h"
#include "shaders/shader.h"

#include <stdlib.h>

static GameCamera *p_gameCamera;
static Shader *p_shader;

int main(void)
{
   // Init game states
   InitGame();

   // GameCamera pointer to pass to raylib's cam init
   p_gameCamera = GetGameCamera();
   p_shader = GetShader();

   // Main game loop
   while (!WindowShouldClose() && !gameShouldClose)
   {
      // Update game states
      if (UpdateGame())
      {
         break;
      }

      // Draw the updates
      BeginDrawing();
      BeginMode2D(p_gameCamera->camera2d);
      BeginShaderMode(*p_shader);
      if (DrawGame())
      {
         break;
      }
      EndShaderMode();
      EndMode2D();
      EndDrawing();
   }

   // Cleanup
   CloseWindow();
   CloseLog();
   return EXIT_SUCCESS;
}
