#include "ConfigSystem.h"

static int MAX_LINE_LENGTH = 80;
static int FILE_LENGTH_LINES = 11;
static char * START_PATTERN = "START CONFIG:";
static char * END_PATTERN = "END CONFIG;";

CONFIG_STATUS_CODES initConfigurationData(ConfigurationData * configDataPointer) {

    if(configDataPointer != NULL) {
        // set defaults to all data
        configDataPointer->version = 0.1;
        configDataPointer->quantum_operation_cycles = 2;
        configDataPointer->processor_cycle_time_msec = 30;
        configDataPointer->process_path = "\0";
        configDataPointer->memory_block_size = 1000;
        configDataPointer->log_to_path = "\0";
        configDataPointer->log_to_code = LOG_TO_CONSOLE;
        configDataPointer->cpu_scheduling_algo = "FIFO";

        return CONFIGURATION_SUCCESS;
    } else {
        printf("Configuration Data Pointer has already been initialized");
        return NULL_DATA_POINTER_ERROR;
    }
}

CONFIG_STATUS_CODES CS_ReadConfigFile(FILE *file, ConfigurationData* configData ){
    if(file == NULL){
        return NULL_FILE_ERROR;
    }
    if(configData == NULL) {
        return NULL_DATA_POINTER_ERROR;
    }

    char line[MAX_LINE_LENGTH];
    /* Get each line until there are none left */
    for (int i = 0; i < FILE_LENGTH_LINES; i ++ )
    {
        if(fgets(line, MAX_LINE_LENGTH, file)){
            /* Print each line */
            if(i == 1) {
                configData->version = strtod(line, (char **)(NULL));
                printf("VERSION IS %d\n", configData->version);
            }
        }    
    }
    return CONFIGURATION_SUCCESS;
}

char * cleanNewline( char * line ) {
    // remove the \n
    for( int i = 0; i < strlen(line); i++ ) {
        if( line[i] != '\n') {
            line[i] = line[i];
        } else {
            line[i] = '\0';
            return line;
        }
    };

    return NULL;
}