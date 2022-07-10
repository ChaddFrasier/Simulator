/**
  * @file cpuScheduler.c
  *
  * @brief This file is used to order the ready queue of the simulation OS version 1.2
  *
  * @details not fully imlimented because FCFS is the only one neede right now
  *
  * @version 1.01
  *          <author>863166 (5 October 2018)
  *          First draft of cpuScheduler file printing functions
  * 
  * @note also has a dispatch function to help run the PCBs
  */


#include "simController.h"

#ifndef CPU_SHEDULER_C
#define CPU_SHEDULER_C

void cpuScheduler(  PCB *pcbPtr, QueueObj **returnQueue, int cpuScheduleCode, char *timeString)
   {

    PCB *tempPCB = pcbPtr;

    QueueObj *tempQueue = *returnQueue;
    
    switch( cpuScheduleCode )
       {
        case CPU_SCHED_FCFS_N_CODE:
            while( tempPCB->next != NULL && !isFull( tempQueue ) ) // if queue is full populate the new queue or wait queue
               {
                // assume single operation
                // create the Ready Queue with a limit for process proformance sake ( const value later )
                if( tempPCB->progRunTime != 0 && !isFull(tempQueue) )
                   {
                    enqueue( tempQueue, tempPCB->progId);
                   } 
                tempPCB = tempPCB->next;
               }
            if( tempPCB->progRunTime != 0 && !isFull(tempQueue) )
               {
                enqueue( tempQueue, tempPCB->progId);
                accessTimer(LAP_TIMER,timeString);
               }
        case CPU_SCHED_SJF_N_CODE:
            
            //printf("num of progs: %d", numberOfPCBs( tempPCB ) );
            tempQueue = getNextShortest( &tempQueue, tempPCB );
            //printf("tempQueue at F = %d : R = %d \n", front(tempQueue), rear(tempQueue));        
        
            
        returnQueue = &tempQueue;
       }
    // set the end of system message if the queue is empty because there is no more processes to run
   }



int dispatchProcess( int processToRun,  PCB **pcbPtr, MemoryDataType **memoryData ,ConfigDataType *configDataPtr, char *timeString )
   {

    int commandMsg;
    int runResult;
    PCB *tempPtr = *pcbPtr;
   
    //displayMetaData( tempPtr->opCodeList );

// IDEA:
// loop through pcb list and find the next process
// cvheckt o see if the process is an IO op or a Processor op
// send process to proper oe ration cycle
    // displays the new RUNNING process
      
    while( tempPtr->progId != processToRun )
       {
        tempPtr = tempPtr->next;
       }  
    
    
    // here i am assuming the correct process was found.
    tempPtr->progState = RUNNING;

    
    
    // otherwise assume only 1 PCB run the only program in the system
    commandMsg = SYSTEM_PROC_RUN_CODE;

    accessTimer( LAP_TIMER, timeString );
    
    logProgramIndicators(commandMsg, configDataPtr->logToCode, timeString, 
                         tempPtr->progId, tempPtr->progRunTime ,configDataPtr->logToFileName );
    

    runResult = runProcess( &tempPtr, memoryData, timeString, configDataPtr);
    
    if( runResult == SEG_FAULT_ERR || tempPtr->progRunTime == 0 )
       {
        tempPtr->progRunTime = 0;
        tempPtr->progState = EXIT;
       }
    else
       {
        tempPtr->progRunTime = getRuntime( tempPtr, configDataPtr->quantumCycles,
                                       configDataPtr->procCycleRate, configDataPtr->ioCycleRate);
       }
    pcbPtr = &tempPtr;
  
    return NO_ERR;
   }

// iterate through the pcb list and set all states to READY

void setReadyQueue( QueueObj *readyQueue, PCB **pcbDataPtr )
   {
    PCB *tempPtr = *pcbDataPtr;
    PCB **head = &tempPtr; 
    
    do
      {
       tempPtr->progState = READY;
       tempPtr = tempPtr->next;
      }while( tempPtr != NULL );

    tempPtr = *head; // get the head address
    pcbDataPtr = &tempPtr; // save the address of temp back into the PCB **
   }



#endif
