#ifndef LOGGER_C
#define LOGGER_C

#include "logger.h"

char* getLogCodeStringDesc(LOG_CODE logTo) {
    switch (logTo)
    {
        case LOG_TO_CONSOLE:
            /* code */
            return "Log to Console";
        case LOG_TO_BOTH:
            return "Log to Both (Console & File)";
        case LOG_TO_FILE:
            return "Log to File";
        default:
            return "Error: Unknown Logger Location Setting";
    }
}

#endif