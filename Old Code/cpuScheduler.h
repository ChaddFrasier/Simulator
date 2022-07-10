#include "simtimer.h"
#include "configAccess.h"
#include "OpQueue.h"
#include "prepPCB.h"
#include "MemManagement.h"

#ifndef CPU_SHEDULER_H
#define CPU_SHEDULER_H

void cpuScheduler(  PCB *pcbPtr ,QueueObj **returnQueue, int cpuScheduleCode, char *timeString);
int dispatchProcess( int processToRun,  PCB **pcbPtr, MemoryDataType **memoryData ,ConfigDataType *configDataPtr, char *timeString );
void setReadyQueue( QueueObj *readyQueue, PCB **pcbDataPtr );

#endif
