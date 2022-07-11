#include "../headers/tests.h"
#include "../../src/SimulatedTimerSystem/SimTimer.h"
#include <string.h>

typedef enum {PASS, FAIL} TEST_STATUS;

// This wll test that the sim timers ZERO_TIMER functionality
TEST{
    char timeString[10] = "0.000000\0";
    // Return a 0 to pass the test
    double time = accessTimer(ZERO_TIMER, timeString);

    printf("Equals = %d", time);

    if( time == 0.000000) {
        return PASS;
    } else {
        return FAIL;
    }

    return FAIL;
}