#include "log.h"

#include <stdarg.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int ensureDirectory(const char *path)
{
   struct stat st = {0};
   if (stat(path, &st) == -1)
   {
      printf("[WARNING]: Log directory didn't exist, creating it.\n");
      if (mkdir(path, 0700) == -1)
      {
         return 0;
      }
   }
   return 1;
}

void WriteLog(int logLevel, const char *text, va_list args)
{
   if (!ensureDirectory("logs"))
   {
      printf("[ERROR]: Could not create log directory.\n");
      return;
   }

   FILE *log_file = fopen(LOG_PATH, "a");

   if (log_file != NULL)
   {
      // Write log level
      switch (logLevel)
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

      // Write log message
      vfprintf(log_file, text, args);
      fprintf(log_file, "\n");
      fclose(log_file);
   }
   else
   {
      printf("ERROR: Could not open log file.\n");
   }
}

void LogMessage(int logLevel, const char *format, ...)
{
   va_list args;
   va_start(args, format);
   WriteLog(logLevel, format, args);
   va_end(args);
}