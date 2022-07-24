#ifndef CONFIG_SYSTEM_C
#define CONFIG_SYSTEM_C

#include "ConfigSystem.h"

static int MAX_LINE_LENGTH = 80;
static int FILE_LENGTH_LINES = 11;
static char * START_PATTERN = "Start Simulator Configuration File:";
static char * END_PATTERN = "End Simulator Configuration File.";

void displayConfigData( ConfigurationData data) {
    printf("Data Structure Contains:\n");
    printf("Version: %.3f\n", data.version);
    printf("Quantum Cycles per Operation: %d\n", data.quantum_operation_cycles);
    printf("Processor Cycle Time: %d\n", data.processor_cycle_time_msec);
    printf("Operation Path: %s\n", data.process_path);
    printf("Max Data Per Operation: %d\n", data.op_block_size);
    printf("Output Log Filepath: %s\n", data.log_to_path);
    printf("Log to setting: %s\n", getLogCodeStringDesc(data.log_to_code));
    printf("Time per IO Operation: %d\n", data.io_cycle_time);
    printf("CPU Scheduler Setting: %s\n", getCPUSchedulerDesc(data.cpu_scheduling_algo));
}

CONFIG_STATUS_CODES initConfigurationData(ConfigurationData * configDataPointer) {
    if(configDataPointer != NULL) {
        // set empty data
        configDataPointer->version = 0.0;
        configDataPointer->quantum_operation_cycles = 0;
        configDataPointer->io_cycle_time = 0;
        configDataPointer->processor_cycle_time_msec = 0;
        configDataPointer->process_path = "NONE\0";
        configDataPointer->op_block_size = 0;
        configDataPointer->log_to_path = "NONE\0";
        configDataPointer->log_to_code = LOG_TO_CONSOLE;
        configDataPointer->cpu_scheduling_algo = FIFOS;
        return CONFIGURATION_SUCCESS;
    } else {
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

// this will proabably be moved eventually
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

/**
 * @brief THIS WILL BE MOVED TO THE CPU SCHEDULER EVENTUALLY
 * 
 * @param algo 
 * @return char* 
 */
char * getCPUSchedulerDesc( CPU_ALGO algo ){
    switch (algo)
    {
        case SJFS:
            return "Shortest Job First - Serial";
        case SRTFS:
            return "Shortest Run Time First - Serial";
        case FIFOS:
            return "First Come First Serve - Serial";
        default:
            break;
    }
}

#endif