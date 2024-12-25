#include "screen.h"
#include "logging/log.h"

#include <stdio.h>

// Default screen sizes
Vector2 SCREEN_DIMENSIONS = {1440, 900};

void InitStartScreen(void)
{
   // Startup screen size
   LogMessage(LOG_DEBUG, "Initializing screen");
   InitWindow(SCREEN_DIMENSIONS.x, SCREEN_DIMENSIONS.y, "Startup Window");

   int monitorCount = GetMonitorCount();
   int monitor = GetCurrentMonitor();

   if (monitor < 0 || monitor >= monitorCount)
   {
      LogMessage(LOG_WARNING, "Monitor index out of range, setting it to 0.");
      monitor = 0;
   }

   LogMessage(LOG_INFO, "Monitor Size: %dx%d", GetMonitorWidth(monitor), GetMonitorHeight(monitor));
   LogMessage(LOG_INFO, "Screen Size: %dx%d", SCREEN_DIMENSIONS.x, SCREEN_DIMENSIONS.y);

   // Close temp window
   LogMessage(LOG_DEBUG, "Closing temporary startup window");
   CloseWindow();
   LogMessage(LOG_DEBUG, "Screen initialization done");
}

void InitMainScreen(void)
{
   // Default window settings
   SetConfigFlags(FLAG_WINDOW_RESIZABLE);

   // Uncomment for screen size % based on monitor size
   // SCREEN_DIMENSIONS.x = GetMonitorWidth(monitor) * WINDOW_MONITOR_RATIO;
   // SCREEN_DIMENSIONS.y = GetMonitorHeight(monitor) * WINDOW_MONITOR_RATIO;

   InitWindow(SCREEN_DIMENSIONS.x, SCREEN_DIMENSIONS.y, SCREEN_TITLE); // Closed in main.c when gameShouldClose = 1
}