// Header Information
/**
  * @file configAccess.h
  *
  * @brief Header file for configAccess.c
  *
  * @details Specifies new types, global constants and
  *          program prototypes for the configAccess.c upload program
  *
  * @version 1.01
  *          863166 (14 September 2018)
  *          First major draft of config data upload program
  *
  * @note none
  */

// Pre-compiler Directives
#ifndef CONFIG_ACCESS_H
#define CONFIG_ACCESS_H

//header file
#include "StringUtils.h"

// global constants
typedef enum { CFG_FILE_ACCESS_ERR = 3,
               CFG_CORRUPT_DESCRIPTOR_ERR,
               CFG_DATA_OUT_OF_RANGE_ERR,
               CFG_CORRUPT_PROMPT_ERR,
               CFG_VERSION_CODE,
               CFG_MD_FILE_NAME_CODE,
               CFG_CPU_SCHED_CODE,
               CFG_QUANT_CYCLES_CODE, 
               CFG_MEM_AVAILABLE_CODE,
               CFG_PROC_CYCLES_CODE,
               CFG_IO_CYCLES_CODE,
               CFG_LOG_TO_CODE,
               CFG_LOG_FILE_NAME_CODE } ConfigCodeMessages;

typedef enum { CPU_SCHED_SJF_N_CODE,
               CPU_SCHED_SRTF_P_CODE,
               CPU_SCHED_FCFS_P_CODE,
               CPU_SCHED_RR_P_CODE,
               CPU_SCHED_FCFS_N_CODE,
               LOGTO_MONITOR_CODE,
               LOGTO_FILE_CODE,
               LOGTO_BOTH_CODE, } ConfigDataCodes;
//Config data type
typedef struct
   {
    double version;
    char metaDataFileName[ 100 ];
    int cpuSchedCode;
    int quantumCycles;
    int memAvailable;
    int procCycleRate;
    int ioCycleRate;
    int logToCode;
    char logToFileName[ 100 ];
   } ConfigDataType; 

//function prototype
int getConfigData( char *fileName, ConfigDataType **configData );
int getDataLineCode( char *dataBuffer );
ConfigDataCodes getCpuSchedCode( char *codeStr );
ConfigDataCodes getLogToCode( char *logToStr );
void displayConfigData( ConfigDataType *configData );
void displayConfigError( int errCode );
void clearConfigData( ConfigDataType **configDataPtr );
void configCodeToString( int code, char *outString );
Boolean valueInRange( int lineCode, int intVal,
                               double doubleVal, char *stringVal);
#endif
