#ifndef HYPEROS_AK_LOGGER_H_
#define HYPEROS_AK_LOGGER_H_

enum
{
    INFO,
    WARNING,
    ERROR,
    DEBUG
};

void info(const char* format, ...);
void warning(const char* format, ...);
void error(const char* format, ...);
void debug(const char* format, ...);

#endif