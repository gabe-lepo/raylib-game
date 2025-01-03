#include "log.h"
#include "utils/timer.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>

static FILE *log_file = NULL;
static int debug;

int ensureDirectory(const char *path)
{
   struct stat st;
   if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
   {
      printf("[INFO]: Directory exists {%s}\n", path);
      return EXIT_SUCCESS;
   }
   else
   {
      printf("[INFO]: Directory does not exist or is not valid, attempting to create it\n");
      int result = mkdir(path, 0700);
      if (result != 0)
      {
         printf("[ERROR]: Error creating logs at {%s}\n\tresult: {%d} | errno: {%d}\n", path, result, errno);
         return EXIT_FAILURE;
      }
      else
      {
         printf("[INFO]: Directory created successfully at {%s}\n", path);
         return EXIT_SUCCESS;
      }
   }
   printf("[ERROR]: Something went wrong!\n\tGlobal ERRNO: {%d}\n", errno);
   return EXIT_FAILURE;
}

void generateLogFilename(char *filename, size_t size)
{
   time_t now = time(NULL);
   struct tm *tm_info = localtime(&now);
   strftime(filename, size, "logs/log_%Y%m%d_%H%M%S.txt", tm_info);
}

int InitLog(int withDebugMessages, int withRaylibMessages)
{
   printf("[INFO]: Initializing logs\n");
   if (withRaylibMessages)
   {
      SetTraceLogCallback(WriteLog);
   }
   else
   {
      SetTraceLogLevel(LOG_NONE);
   }

   debug = withDebugMessages;

   int result = ensureDirectory(LOG_DIR);
   if (result)
   {
      printf("[ERROR]: Couldn't create log directory for some reason:\n\t{%d}\n", result);
      return EXIT_FAILURE;
   }

   char logFilename[256];
   generateLogFilename(logFilename, sizeof(logFilename));
   log_file = fopen(logFilename, "a");

   if (log_file == NULL)
   {
      printf("[ERROR]: Log file is NULL\n");
      return EXIT_FAILURE;
   }

   printf("[INFO]: Logging started in {%s}\n", logFilename);
   return EXIT_SUCCESS;
}

void WriteLog(int logLevel, const char *text, va_list args)
{
   TimerText *p_timerText = GetGameTime();
   if (log_file != NULL)
   {
      // Write timestamp
      fprintf(log_file, "{%s} - ", p_timerText->text);

      // Write log level
      switch (logLevel)
      {
      case LOG_INFO:
         fprintf(log_file, "[INFO]: ");
         break;
      case LOG_DEBUG:
         if (!debug)
         {
            return;
         }
         fprintf(log_file, "[DEBUG]: ");
         break;
      case LOG_WARNING:
         fprintf(log_file, "[WARNING]: ");
         break;
      case LOG_ERROR:
         fprintf(log_file, "[ERROR]: ");
         break;
      case LOG_FATAL:
         fprintf(log_file, "[FATAL]: ");
         break;
      default:
         fprintf(log_file, "[UNKNOWN]: ");
      }

      // Write log message
      vfprintf(log_file, text, args);
      fprintf(log_file, "\n");

      // If we want to debug, ensure we flush to the file constantly
      if (debug)
      {
         fflush(log_file);
      }
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

void CloseLog(void)
{
   if (log_file != NULL)
   {
      fclose(log_file);
      log_file = NULL;
      printf("[INFO]: Log file closed\n");
      return;
   }
   printf("[WARNING]: Log file was already closed!\n");
   return;
}