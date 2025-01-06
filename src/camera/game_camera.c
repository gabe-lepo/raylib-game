#include "game_camera.h"
#include "game/screen.h"
#include "logging/log.h"

static GameCamera gameCamera;

void InitGameCamera(Player *player)
{
   gameCamera.camera2d.target = (Vector2){player->object.shape.rectangle.x, player->object.shape.rectangle.y};
   gameCamera.camera2d.offset = (Vector2){SCREEN_DIMENSIONS.x / 2.0f, SCREEN_DIMENSIONS.y / 2.0f};
   gameCamera.camera2d.rotation = 0.0f;
   gameCamera.camera2d.zoom = 1.0f;

   LogMessage(LOG_INFO, "Camera initialized with params:\n"
                        "\tTarget: {%s}\n"
                        "\tOffset: {%.0fx%.0f}\n"
                        "\tRotation: {%.0f}\n"
                        "\tZoom: {%.0f}",
              player->object.label,
              gameCamera.camera2d.offset.x, gameCamera.camera2d.offset.y,
              gameCamera.camera2d.rotation,
              gameCamera.camera2d.zoom);
}

void UpdateGameCamera(Player *player)
{
   // Zoom
   // gameCamera.camera2d.zoom += GetMouseWheelMove() * 0.05f;

   // if (IsKeyPressed(KEY_R))
   //    gameCamera.camera2d.zoom = 1.0f;

   // gameCamera.camera2d.zoom = Clamp(gameCamera.camera2d.zoom, 0.5f, 1.5f);

   // Retarget player
   Vector2 playerCenter = {player->object.shape.rectangle.x + (player->object.shape.rectangle.width / 2.0f),
                           player->object.shape.rectangle.y + (player->object.shape.rectangle.height / 2.0f)};
   Vector2 cameraTarget = gameCamera.camera2d.target;

   const float followSpeed = 0.1f;

   cameraTarget.x = Lerp(cameraTarget.x, playerCenter.x, followSpeed);
   // cameraTarget.y = Lerp(cameraTarget.y, playerCenter.y, followSpeed);

   gameCamera.camera2d.target = cameraTarget;
}

GameCamera *GetGameCamera(void)
{
   return &gameCamera;
}

void CleanUpGameCamera(void)
{
   // TOOD
}

void CenterGameCamera(void)
{
   gameCamera.camera2d.target = (Vector2){SCREEN_DIMENSIONS.x / 2.0f, SCREEN_DIMENSIONS.y / 2.0f};
   gameCamera.camera2d.zoom = 1.0f;
}