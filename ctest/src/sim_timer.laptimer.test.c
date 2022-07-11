#include "../headers/tests.h"
#include "../../src/SimulatedTimerSystem/SimTimer.h"

// This wll test that the sim timers LAP_TIMER ability works to delay the fake processor for an amount of time
TEST{
    char timeString[100];

    // Return a 0 to pass the test
    double zeroTime = accessTimer(ZERO_TIMER, timeString);
    runTimer(100);
    double newTime = accessTimer(LAP_TIMER, timeString);

    if(newTime != zeroTime) {
        return 0;
    }
    else {
        return 1;
    }
}