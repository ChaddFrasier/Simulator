// pre compiler directives
#ifndef SIM_CONTROLLER_H
#define SIM_CONTROLLER_H

// header files
#include "simtimer.h"
#include "prepPCB.h"
#include "OpQueue.h"
#include "cpuScheduler.h"
#include "MetaDataAccess.h"
#include "configAccess.h"
#include "StringUtils.h"
#include "sysLog.h"
#include "MemManagement.h"

// type definitions

// set to 100 so i can distinguish system and process commands
//    from config and meta data commands

typedef enum { SYSTEM_START_CODE = 100,
               SYSTEM_CREATE_PCB_CODE,
               SYSTEM_PROC_INIT_CODE,
               SYSTEM_PROC_READY_CODE,
               SYSTEM_PROC_SELECT_CODE,
               SYSTEM_PROC_RUN_CODE,
               SYSTEM_PROC_STOP_CODE,
               SYSTEM_STOP_CODE,
               TIMER_INTERUPT,
               NO_INTERUPT,
               END_LOOP
               } SystemCodes;

typedef enum { 
               PROCESS_OUTPUT_CODE,
               PROCESS_MEMORY_CODE,
               PROCESS_INPUT_CODE,
               PROCESS_RUN_CODE,
               } ProcessCodes;



// prototype functions
void *IOthread(void *ptr ); // thread

void processorOperation( OpCodeType *opCode , int quantumCycles, 
                         int cycleTime, char *timeString );
int getCommand            ( char commandMsg);
int runSimulation( OpCodeType *mdData, ConfigDataType *configDataPtr, PCB *pcbDataPtr);
void createDisplayString  ( char *timerString, char *indicatorString, char *opLetterString,
                            char *opName , char *outputString);
void getOpLetterString    (OpCodeType opCode, char **returnString);
void displaySystemCommand ( int code , char *timeString);
void displayProgramSelect ( int commandMsg, char *timeString , int progId, int progRunTime );
int runProcess( PCB **pcbPtr, MemoryDataType **memData, char *timeString, ConfigDataType *configDataPtr);
int checkInterupts        (void);
void displayInternalString( int commandMsg, char *timeString , int progId, 
                             char *nameString, char *startEndString );
void removeInnerPCB( PCB **pcbPtr, PCB *tempPCB );

#endif
