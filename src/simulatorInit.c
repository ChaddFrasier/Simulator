/**
 * 
 * MAIN FILE
 * 
 * 
*/
#ifndef SIMULATOR_INIT_C
#define SIMULATOR_INIT_C

#include "ConfigSystem/ConfigSystem.h"
#include "SimulatedTimerSystem/SimTimer.h"

int Run_OS_Sim(void) {

    FILE *file = NULL;
    ConfigurationData simConfig;
    CONFIG_STATUS_CODES status = initConfigurationData(&simConfig);

    // check the values that have been set during initialization
    displayConfigData(simConfig);

    if(status == CONFIGURATION_SUCCESS && simConfig.version > 0) {
        file = fopen("../../data/config/basic.cnf", "r");

        // set new configuration data

        // close the file when finished
        fclose(file);
    }

    return status;
}

int main(int argc, char *argv[]) {
    return (int)Run_OS_Sim();
}
#endif