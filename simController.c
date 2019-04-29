// Header Information
/**
  * @file simController.c
  *
  * @brief main driver file for the simulation
  *
  * @details collects data from a config file, and then stores the data 
  *              in a data structure for later 
  *
  * @version 1.01
  *         863166 (8 October 2018)
  *         First major draft of the simulation driver function
  * 
  * @note Requires simController.h
  */


// precompiler directives
#ifndef SIM_CONTROLLER_C
#define SIM_CONTROLLER_C

// header files
#include <pthread.h>
#include <stdio.h>
#include <unistd.h> 

#include "simController.h"
#include "MetaDataAccess.h"



void *IOthread(void *threadOpTime)
   {
    int *timerValue = (int *) threadOpTime;
    runTimer( *timerValue );
    return threadOpTime; 
   }

/*
Function Name: runProcess
Algorithm: This is a function that is designed to take a single PCb along with the counter and other data needed to , it will aso be able 
Preconditions: this requires valid pointers to config and data file
Postcondition: updates state of 
Exception:
*/
int runProcess( PCB **pcbPtr, MemoryDataType **memData, char *timeString, ConfigDataType *configDataPtr)
   {
    pthread_t thread1;
    int statusCode;
    char *startEnd;
    int memResult = NO_ERR;

    PCB *tempPCB = *pcbPtr; 
    OpCodeType *tempList = tempPCB->opCodeList; 
    MemoryDataType *tempMemData = *memData;
  
// this is the method that i could check for preetiveness later
    switch( configDataPtr->cpuSchedCode )
       {
        default: // nonpreemtion
            // loop through the whole opcode list
            while( tempList->next != NULL && memResult == NO_ERR )
               {
                // excecute input / output  thread
                if( tempList->opLtr == (int)'I' || tempList->opLtr == (int)'O' )
                   {
                    //thread a timer and return
                    statusCode = getCommand( tempList->opLtr );
                    accessTimer( LAP_TIMER, timeString);
        
                    startEnd = "start";
                    // check log to setting
                    logInternalString( statusCode, configDataPtr->logToCode, timeString , tempPCB->progId, 
                                       tempList->opName, startEnd, configDataPtr->logToFileName );    

                    // IO operation
                    accessTimer( LAP_TIMER, timeString );
                    int threadOpTime = tempList->opValue  * configDataPtr->ioCycleRate;
// in order to cleanly pass multiple parameiers i will have to make a struct that holds all the neccessqry data for the thread
                    pthread_create( &thread1, NULL, IOthread, (void *) &threadOpTime );

                    startEnd = "end"; 
                    pthread_join(thread1,NULL);
                    accessTimer( LAP_TIMER, timeString );

                    // display results at end of thread
                    logInternalString( statusCode, configDataPtr->logToCode, timeString , tempPCB->progId, 
                                       tempList->opName, startEnd, configDataPtr->logToFileName );
                    
            
                    tempPCB->progCounter++;
                   }
                // check for start op application
                else if ( tempList->opLtr != (int)'A' && tempList->opLtr != (int)'M' )
                   {
                    // appliocation run detected
                    statusCode = getCommand( tempList->opLtr );
                    accessTimer( LAP_TIMER, timeString);

                    startEnd = "start";

                    // check log to file setting
                    logInternalString( statusCode, configDataPtr->logToCode, timeString , tempPCB->progId, 
                                       tempList->opName, startEnd, configDataPtr->logToFileName );
                    

                    // execute a processor cycle with a single opCode
                    processorOperation( tempList , configDataPtr->quantumCycles, configDataPtr->ioCycleRate, timeString);

                    // operation execuded and finished
                    startEnd = "end";
                    // check log file
                    logInternalString( statusCode, configDataPtr->logToCode, timeString , tempPCB->progId, 
                                       tempList->opName, startEnd, configDataPtr->logToFileName );
                    
                    }
                else if ( (int)tempList->opLtr == (int)'M' )
                   {
                    // appliocation run detected
                    statusCode = getCommand( tempList->opLtr );
                    accessTimer( LAP_TIMER, timeString);

                    startEnd = "start";

                    // check log to file setting
                    logMemString( statusCode, configDataPtr->logToCode, timeString , tempPCB->progId, 
                                       tempList->opName, startEnd, configDataPtr->logToFileName, getSegId( tempList->opValue ),
                                       getBaseValue( tempList->opValue ), getLimitValue( tempList->opValue ) );
                    

                    // execute a processor cycle with a single opCode
                    //printf("--RUN THE MEMORY MANAGMENT UNIT--\n");
                    memResult = memoryOperation( tempList, tempPCB, &tempMemData, timeString );
                    
                   /* if( tempMemData != NULL )
                       {
                        printf("tempMem = %d\n", tempMemData->segId );
                        if( tempMemData->next != NULL)
                           {
                            printf("tempMem->next = %d\n", tempMemData->next->segId );
                           }
                       }*/
                      
                    if( memResult == NO_ERR )
                       {
                        // operation execuded and finished
                        startEnd = "end";
                        accessTimer( LAP_TIMER, timeString );
                        // check log file
                        logMemString( statusCode, configDataPtr->logToCode, timeString , tempPCB->progId, 
                                       tempList->opName, startEnd, configDataPtr->logToFileName, getSegId( tempList->opValue ),
                                       getBaseValue( tempList->opValue ), getLimitValue( tempList->opValue ) );
                               
                        tempPCB->progCounter++;
                       }
                    else
                       {
                        displayMemoryError( memResult );
                        tempMemData = eraseMemory( tempMemData );
                        //removeInnerPCB( pcbPtr, tempPCB );
                        return memResult;
                       }
                   
                   }
            // next loop
            tempList = tempList->next;
            }

       }   
    tempPCB->opCodeList = tempList; // save the current list
    pcbPtr = &tempPCB;              // save the temp PCB back into the PCB struct
    memData = &tempMemData;    
    return NO_ERR;
   }


void removeInnerPCB( PCB **pcbPtr, PCB *tempPCB )
   {  
    PCB *localPCB = *pcbPtr;
    PCB *last;
    while( localPCB->next != NULL && tempPCB->progId == localPCB->progId )
       {
        last = localPCB;
        localPCB = localPCB->next;
       }
    if( tempPCB->progId == localPCB->progId )
       {
        if( last != NULL)
           {
            last->next = localPCB->next;
            localPCB = last;
           }
        else
           {
            last = localPCB;
            localPCB = localPCB->next;
            free( last );
           }
        pcbPtr = &localPCB;
       }
    // no change
   }

/*
Function Name: processorOperation
Algorithm: This is a function that simulates the actions of a 
           cpu by decrementing the opCode value and running cycles of specified times
           checks for interupts after each quantum cycle
Precondition: requires a single op code and program counter as well as the config data 
              peices for cycle operations
Postcondition: none
Exceptions: none
*/
void processorOperation( OpCodeType *opCode , int quantumCycles, int cycleTime, char *timeString )
   {
    // check the cycle code on the opCode
    if( opCode->opValue > 0 )
       { 
        accessTimer( 1, timeString);
        // run timer for 3 cycles
        runTimer( quantumCycles * cycleTime );
        // increment the opcode Value
        opCode->opValue -= 3;
        accessTimer( 1, timeString);
       }
    // check for interupts : none at this stage yet
    if( checkInterupts() == NO_INTERUPT )
       {
        // preform the next op
       }
   }




/*
Function Name: checkInterupts
Algorithm: checks for interupt calls
Precondition: none
Postcondition: returns interupt code
Exceptions: this is a stub right now */
int checkInterupts(void)
   {
    return NO_INTERUPT;
   }
#endif
