#include "log.h"

#include <stdarg.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

void WriteLog(TraceLogLevel level, const char *format, ...)
{
   // Ensure directory exists
   struct stat st = {0};
   if (stat("logs", &st) == -1)
   {
      printf("DEBUG: Log directory didn't exist, creating it.\n");
      mkdir("logs", 0700);
   }

   FILE *log_file = fopen(LOG_PATH, "a");

   if (log_file != NULL)
   {
      switch (level)
      {
      case LOG_INFO:
         fprintf(log_file, "[INFO]: ");
         break;
      case LOG_DEBUG:
         fprintf(log_file, "[DEBUG]: ");
         break;
      case LOG_WARNING:
         fprintf(log_file, "[WARNING]: ");
         break;
      case LOG_ERROR:
         fprintf(log_file, "[ERROR]: ");
         break;
      default:
         fprintf(log_file, "[UNKNOWN]: ");
      }

      va_list args;
      va_start(args, format);
      vfprintf(log_file, format, args);
      va_end(args);
      fprintf(log_file, "\n");
      fclose(log_file);
   }
   else
   {
      printf("ERROR: Could not open log file.\n");
   }
}