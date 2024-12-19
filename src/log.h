#ifndef LOG_H
#define LOG_H

#include "raylib.h"

#include <stdio.h>

#define LOG_PATH "logs/log.txt"

void WriteLog(TraceLogLevel level, const char *format, ...);

#endif // LOG_H