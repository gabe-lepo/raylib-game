#include "screen.h"
#include "log.h"

#include <stdio.h>

// Default screen sizes
int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 450;

void InitScreenSize(void)
{
   // Startup screen size
   LogMessage(LOG_DEBUG, "Initializing screen");
   InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Startup Window");

   int monitorCount = GetMonitorCount();
   int monitor = GetCurrentMonitor();

   if (monitor < 0 || monitor >= monitorCount)
   {
      LogMessage(LOG_WARNING, "Monitor index out of range, setting it to 0.");
      monitor = 0;
   }

   // Uncomment for screen size % based on monitor
   // SCREEN_WIDTH = GetMonitorWidth(monitor) * WINDOW_MONITOR_RATIO;
   // SCREEN_HEIGHT = GetMonitorHeight(monitor) * WINDOW_MONITOR_RATIO;

   LogMessage(LOG_INFO, "Monitor Size: %dx%d", GetMonitorWidth(monitor), GetMonitorHeight(monitor));
   LogMessage(LOG_INFO, "Screen Size: %dx%d", SCREEN_WIDTH, SCREEN_HEIGHT);

   // Close temp window
   LogMessage(LOG_DEBUG, "Closing temporary startup window");
   CloseWindow();
   LogMessage(LOG_DEBUG, "Screen initialization done");
}