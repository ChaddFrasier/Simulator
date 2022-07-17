#ifndef CONFIG_SYSTEM_H
#define CONFIG_SYSTEM_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "../Logger/logger.h"

typedef enum CONFIG_STATUS_CODES{
    MALFORMED_FILE_ERROR,
    NULL_FILE_ERROR,
    NULL_DATA_POINTER_ERROR,
    CONFIGURATION_SUCCESS,
} CONFIG_STATUS_CODES;

typedef enum CPU_ALGO {
    SJFS=50,
    FIFOS,
    SRTFS,
} CPU_ALGO;

typedef struct ConfigurationData {
    double version;
    char * process_path; // the path to the 'execution' file for this CPU operation
    CPU_ALGO cpu_scheduling_algo;
    int quantum_operation_cycles; // the number of cycles per quantum operation of the CPU
    int processor_cycle_time_msec; // how long the timer will wait for each normal operation cycle
    int op_block_size; // each process will have this much MBs
    int io_cycle_time; // how long the timer will wait for each io operation cycle
    LOG_CODE log_to_code; // where to log the stdout
    char * log_to_path; // file to log to if needed
} ConfigurationData;

void displayConfigData( ConfigurationData data);
CONFIG_STATUS_CODES initConfigurationData(ConfigurationData* data);
CONFIG_STATUS_CODES CS_ReadConfigFile(FILE *file, ConfigurationData* configData);
char * cleanNewline( char * line);


// will probably get moved eventually 
char * getCPUSchedulerDesc(CPU_ALGO algoCode);

#endif