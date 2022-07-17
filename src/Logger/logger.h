#ifndef LOGGER_H
#define LOGGER_H

typedef enum LOG_CODE{
    LOG_TO_BOTH,
    LOG_TO_CONSOLE,
    LOG_TO_FILE
} LOG_CODE;

char* getLogCodeStringDesc(LOG_CODE logTo);

#endif