/**
 * 
 * MAIN FILE
 * 
 * 
*/
#include "ConfigSystem/ConfigSystem.h"
#include "SimulatedTimerSystem/SimTimer.h"

int Run_OS_Sim(void) {

    FILE *file = NULL;
    ConfigurationData simConfig;
    CONFIG_STATUS_CODES status = initConfigurationData(&simConfig);

    if(status == CONFIGURATION_SUCCESS && simConfig.version > 0) {
        file = fopen("../../data/config/basic.cnf", "r");

        printf("RETURNED %s\n", ((CS_ReadConfigFile( file, &simConfig ) == CONFIGURATION_SUCCESS)?"SUCCESS": "FAIL" ) );
        printf("RETURNED Data %s\n", (simConfig.version)?"SUCCESS": "FAIL" );

        fclose(file);
    }

    return status;
}

int main(int argc, char *argv[]) {
    return (int)Run_OS_Sim();
}