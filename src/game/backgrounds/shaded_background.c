#include "raylib.h"
#include "shaded_background.h"
#include "game/screen.h"
#include "objects/player.h"

static Rectangle backgroundMask;
static Player *p_player;

void InitShadedBackground(void)
{
   backgroundMask = (Rectangle){
       .x = 0,
       .y = 0,
       .width = SCREEN_DIMENSIONS.x,
       .height = SCREEN_DIMENSIONS.y,
   };

   p_player = GetPlayer();
}

void UpdateShadedBackground(void)
{
   // Center background with player
   backgroundMask.x = p_player->object.shape.rectangle.x - backgroundMask.width + (SCREEN_DIMENSIONS.x / 2);
   backgroundMask.y = p_player->object.shape.rectangle.y - backgroundMask.height + (SCREEN_DIMENSIONS.y / 2);
}

void DrawShadedBackground(void)
{
   DrawRectangleRec(backgroundMask, BLACK);
}

void CleanupShadedBackground(void)
{
   // TODO
}
