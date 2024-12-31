#ifndef TIMER_H
#define TIMER_H

#include "raylib.h"

typedef struct TimerText
{
   int minutes;
   int seconds;
   char text[16];
   int size;
   Vector2 position;
   Color color;
} TimerText;

void InitTimer(void);
void UpdateTimer(void);
void DrawTimer(void);

#endif // TIMER_H
