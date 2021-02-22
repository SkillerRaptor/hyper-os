#include <AK/logger.h>

#include <stdarg.h> 
#include <stdio.h>
#include <AK/serial.h>

static void log_string(int status, const char* format, ...)
{
    const char* string = "";

    switch (status)
    {
    case INFO:
        string = "\033[39m[ \033[32mINFO \033[39m] ";
        break;
    case WARNING:
        string = "\033[39m[ \033[33mWARNING \033[39m] ";
        break;
    case ERROR:
        string = "\033[39m[ \033[31mERROR \033[39m] ";
        break;
    case DEBUG:
        string = "\033[39m[ \033[36mDEBUG \033[39m] ";
        break;
    default:
        string = "";
        break;
    }

    va_list args;
    va_start(args, format);

    printf(string);
    printf(format, args);

    va_end(args);

    serial_write('\n');
}

void info(const char* format, ...)
{
    va_list args;
    va_start(args, format);

    log_string(INFO, format, args);

    va_end(args);
}

void warning(const char* format, ...)
{
    va_list args;
    va_start(args, format);

    log_string(WARNING, format, args);

    va_end(args);
}

void error(const char* format, ...)
{
    va_list args;
    va_start(args, format);

    log_string(ERROR, format, args);

    va_end(args);
}

void debug(const char* format, ...)
{
    va_list args;
    va_start(args, format);

    log_string(DEBUG, format, args);

    va_end(args);
}