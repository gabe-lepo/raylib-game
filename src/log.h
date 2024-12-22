#ifndef LOG_H
#define LOG_H

#include "raylib.h"

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#define LOG_DIR "logs/"

int InitLog(int withDebugMessages);
void WriteLog(int logLevel, const char *text, va_list args);
void LogMessage(int logLevel, const char *format, ...);
void CloseLog(void);

#endif