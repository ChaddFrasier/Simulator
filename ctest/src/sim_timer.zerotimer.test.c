#include "../headers/tests.h"
#include "../../src/SimulatedTimerSystem/SimTimer.h"
#include <string.h>

// This wll test that the sim timers ZERO_TIMER functionality
TEST{
    char timeString[10] = "0.000000\0";
    double time = accessTimer(ZERO_TIMER, timeString);

    if( time == 0.000000) {
        return PASS;
    } else {
        return FAIL;
    }
    return FAIL;
}