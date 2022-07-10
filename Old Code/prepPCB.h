//precompiler directives
#ifndef PREP_PCB_H
#define PREP_PCB_H
//header files
#include <stdio.h>
#include <stdlib.h>
#include "configAccess.h"
#include "MetaDataAccess.h"

// global constants

// PCB struct

typedef enum{ READY,
              WAIT,
              NEW,
              RUNNING,
              BLOCK,
              EXIT,
              }State;

typedef enum{ SYSTEM,
              APPLICATION,
              PROCESS,
              MEMORY,
              INPUT,
              OUTPUT,
              }OpLetter;

typedef enum{ ACCESS,
              ALLOCATE,
              END,
              HARD_DRIVE,
              KEYBOARD,
              PRINTER,
              MONITOR,
              RUN,
              START,
              }OpDes;
              

typedef struct PCB{
               int progId;
               int progCounter;
               int progRunTime;
               State progState;
              
               OpCodeType *opCodeList;
               struct PCB *next;
              }PCB;

//function prototypes
int loadPCBs( OpCodeType *mdData, ConfigDataType *configData, PCB **pcbDataPtr, char *timeString );
PCB *createPCB( OpCodeType *mdData, ConfigDataType *configData, PCB *pcbPtr , int progId );
int getOpCodeList(OpCodeType *dataPtr, PCB **destPtr );
PCB *clearProcessBlock(PCB *pcbPtr);
int getRuntime( PCB *pcbList , int quantum, int cycleTime, int ioCycleTime );
int getCycles( char opLtr, int procCycleTime, int ioCycleTime);
PCB *addPCB( PCB *newPCB, PCB *localPtr );

int numberOfPCBs( PCB *localPtr );

#endif
