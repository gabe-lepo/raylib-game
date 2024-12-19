#include "raylib.h"
#include "timer.h"

#include <stdio.h>

static float gameTime = 0.0f;

void InitTimer()
{
   gameTime = 0.0f;
}

void UpdateTimer()
{
   gameTime += GetFrameTime();
}

void DrawTimer()
{
   int minutes = (int)(gameTime / 60);
   int seconds = (int)(gameTime) % 60;
   char timerText[10];
   sprintf(timerText, "%02d:%02d", minutes, seconds);
   DrawText(timerText, 10, 10, 20, BLUE);
}
