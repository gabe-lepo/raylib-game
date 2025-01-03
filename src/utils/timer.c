#include "timer.h"
#include "game/screen.h"

#include <stdio.h>

static float gameTime;
static TimerText timerText;

/**
 * @brief Initialize TimerText struct and internal game time counter.
 * @return void - Operates on internal TimerText struct
 */
void InitTimer(void)
{
   gameTime = 0.0f;

   timerText.position.x = SCREEN_EDGE_PADDING;
   timerText.position.y = SCREEN_EDGE_PADDING;
   timerText.size = 20;
   timerText.color = BLUE;
}

/**
 * @brief Update TimerText struct
 * @return void - Operates on internal TimerText struct
 */
void UpdateTimer(void)
{
   gameTime += GetFrameTime();

   timerText.minutes = (int)(gameTime / 60);
   timerText.seconds = (int)(gameTime) % 60;
   sprintf(timerText.text, "%02d:%02d", timerText.minutes, timerText.seconds);
}

/**
 * @brief Draw the TimerText struct
 * @return void - Operates on internal TimerText struct
 */
void DrawTimer(void)
{
   DrawText(timerText.text, timerText.position.x, timerText.position.y, timerText.size, timerText.color);
}

/**
 * @brief Get the Game Time object
 *
 * @return TimerText*
 */
TimerText *GetGameTime(void)
{
   return &timerText;
}