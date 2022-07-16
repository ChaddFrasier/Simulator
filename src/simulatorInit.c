/**
 * 
 * MAIN FILE
 * 
 * 
*/
#include <stdbool.h>
#include "ConfigSystem/ConfigSystem.h"

int Run_OS_Sim(void) {

    FILE *file = NULL;
    ConfigurationData simConfig;

    file = fopen("../../data/config/basic.cnf", "r");


    printf("RETURNED %s\n", ((CS_ReadConfigFile( file, &simConfig ) == CONFIGURATION_SUCCESS)?"SUCCESS": "FAIL" ) );
    printf("RETURNED Data %s\n", (!(bool) simConfig.version)?"SUCCESS": "FAIL" );

    fclose(file);
    return 0;
}

int main(int argc, char *argv[]) {
    return (int)Run_OS_Sim();
}