// Header Information
/**
  * @file pa03.c
  *
  * @brief This is a driver function for the whole config, and 
  *          metadata upload process
  *
  * @details Uses configAccess.c & MetaDataAccess.c functions to read the 
  *           config data in and then calls the function to run the driver function
  *
  * @version 1.01
  *         863166 (8 October 2018)
  *         First major draft of PA02 ( single process execution )
  * 
  * @note needs simController.h
  */

//Precomplier Directive
#ifndef PA_03_C
#define PA_03_C

// header files
#include "simController.h"

/*
Function Name: main
Algorithm: driver function to upload the config data and 
           upload the resulting metadata file 
Precondition: none
PostCondition: return zero (0) on success
Exceptions: none
Notes: this is the 
*/
int main( int argc, char **argv )
   {

    // initialize functions/ variables
    int configAccessResult, mdAccessResult, commandCode; // holds message enums
    char configFileName[ MAX_STR_LEN ];     // holds the config file
    char mdFileName[ MAX_STR_LEN ];         // holds metadata file
    ConfigDataType *configDataPtr = NULL;   // pointer to Config struct
    OpCodeType *mdData = NULL;              // pointer to MetaData struct
    PCB *pcbDataPtr = NULL;                 // pointer to PCB struct 
    MemoryDataType *memData = NULL;
    QueueObj *readyQueue = createQueue(10); // create ready queue       
    char timeString[ MAX_STR_LEN ];         // holds metadata file
    

    // check for not correct number of command line arguments (two)
    if( argc < 2 )
       {
        // print missing command line argument error
        printf("ERROR: Program requires file name for config file" );
        printf("as a command line argument\n" );
        printf("Program Terminated\n" );
        // return non-normal program result
        return 1;
       }

    // get data from configuration file
       // function: copyString, getConfigData
    copyString( configFileName, argv[ 1 ]);
    configAccessResult = getConfigData( configFileName, &configDataPtr );
  
    commandCode = STARTER_CODE;
    StarterLog( commandCode, configDataPtr->logToCode, configDataPtr->logToFileName ); 

   
    commandCode = UPLOAD_CONFIG_CODE;
    // log to file
    StarterLog(commandCode, configDataPtr->logToCode, configDataPtr->logToFileName );


    // check for successful upload
    if( configAccessResult != NO_ERR )
       {
        // display configuration upload error
          // function: displayConfigError
        displayConfigError( configAccessResult );
        return 1;
       }

    commandCode = UPLOAD_META_CODE;
    //log to file
    StarterLog(commandCode, configDataPtr->logToCode, configDataPtr->logToFileName );


    // get data from meta data file
       // function: copyString, getOpCodes
    copyString( mdFileName, configDataPtr-> metaDataFileName );
    mdAccessResult = getOpCodes( mdFileName, &mdData );
    
    // check for successful upload
    if( mdAccessResult != NO_ERR )
       {
        // display meta data error message
          // function: displayMetaDataError
        displayMetaDataError( mdAccessResult );

        return 1;
       }


    commandCode = SIM_BEGIN_CODE;
    // log to file
    StarterLog(commandCode, configDataPtr->logToCode, configDataPtr->logToFileName );

    // check for simulator start command
    int runResult;
    commandCode = SYSTEM_START_CODE;
    accessTimer(ZERO_TIMER, timeString);
        
    // check the log code and do what it says 
    SystemLogPrint( commandCode, configDataPtr->logToCode, timeString, configDataPtr->logToFileName );
      


    // simulation is shutting down 
    accessTimer( LAP_TIMER, timeString );


    // display that we are loading PCBs
    commandCode = SYSTEM_CREATE_PCB_CODE; 
    // write to  file
    SystemLogPrint(commandCode, configDataPtr->logToCode, timeString, configDataPtr->logToFileName );
 
    // load PCBs
    runResult = loadPCBs(mdData, configDataPtr, &pcbDataPtr,  timeString);
    
    // notify system processes initalized
    if( runResult == NO_ERR )
       {
        commandCode = SYSTEM_PROC_INIT_CODE;
       }
    
    // write to  file
    SystemLogPrint(commandCode ,configDataPtr->logToCode ,timeString, configDataPtr->logToFileName );
 
    // lap timer string
    accessTimer(LAP_TIMER,timeString);

    // organize the ready queue before first execution loop
    cpuScheduler( pcbDataPtr , &readyQueue, configDataPtr->cpuSchedCode, timeString);

    // set all processes in ready
    setReadyQueue( readyQueue, &pcbDataPtr );
    
    // notify processes ready
    commandCode = SYSTEM_PROC_READY_CODE;
    accessTimer( LAP_TIMER, timeString );

    // write to  file
    SystemLogPrint(commandCode, configDataPtr->logToCode, timeString, configDataPtr->logToFileName );

   //MAIN LOOP BEGINS HERE
    // pick process to run 
    // the cpu scheduler will handle the ready queue oerder therefore the next process to run is at the front of the queue
      // dispatchProcess() will take in the next program that needs to run as well as the list of pcbs, 
      // it will find the pcb that is needed using the value from dequeue and then run a quantum cycle overation on that pcb
      // it will either run an I/O op and return or 

//============MAIN LOOP======================================================================================================

    do // do (while the ready queue is not empty)
       {
        // check if peemtion is needed

        // get current time update
        accessTimer( LAP_TIMER, timeString );
      
        // init commandCode
        commandCode = SYSTEM_PROC_SELECT_CODE;

        // grab a temp of the data head
        PCB *tempPCBPtr = pcbDataPtr;
            
   
     // loop while the current data head is is not the next in the queue 
        while( tempPCBPtr->progId != front(readyQueue) )
           {
            // next pcb
            tempPCBPtr = tempPCBPtr->next;
           }
        //printf("selected pcb: %d\n", tempPCBPtr->progId);
        // assume found and check to see if runtime of the found process is 0
        if( tempPCBPtr->progRunTime == 0)
           {
            // set command code and exit the loop
            commandCode = SYSTEM_STOP_CODE;
            break;
           }

       // display command
       logProgramIndicators( commandCode, configDataPtr->logToCode, timeString , 
                              tempPCBPtr->progId, tempPCBPtr->progRunTime, 
                                                  configDataPtr->logToFileName );
       // dispatch the program

       runResult = dispatchProcess( dequeue( readyQueue ), &pcbDataPtr, &memData, configDataPtr, timeString );

       // commandCode = process stopped
       
       commandCode = SYSTEM_PROC_STOP_CODE;

       // log to according to code
       logProgramIndicators( commandCode, configDataPtr->logToCode, timeString, 
                                              tempPCBPtr->progId, tempPCBPtr->progRunTime, 
                                                           configDataPtr->logToFileName );
       
        // set the ready queue
           // Note: the queue will return a pointer to a 0 runtime process that is why it is checked for the end at the top
//        printf("0 false, 1 true: %d\n", isEmpty(readyQueue) );
        cpuScheduler( pcbDataPtr , &readyQueue, configDataPtr->cpuSchedCode, timeString);
  //      printf("0 false, 1 true AFTER: %d\n", isEmpty(readyQueue) );
        // end : do (while the ready queue is not empty)
       }while( !isEmpty( readyQueue ));

    // log the OS stop message
    SystemLogPrint( commandCode , configDataPtr->logToCode, timeString, configDataPtr->logToFileName );

     // check the success of the run
     if( runResult == NO_ERR )
        {
         //  log simulation end message
         commandCode = SIM_END_CODE;
         StarterLog(commandCode , configDataPtr->logToCode, configDataPtr->logToFileName );
        }
     else
        {
         // display error
         clearConfigData( &configDataPtr );
         mdData = clearMetaDataList( mdData );
         pcbDataPtr = clearProcessBlock( pcbDataPtr );
         clearQueue( &readyQueue );
         printf("SOMETHING HORRIBLE HAPPENED! \n");
         return 1;
        }

    // clear data
    // shut down whole program, clean up program
      // clear meta data, config data, queue data, pcb data. 
        //   function: clearMetaDataList
        //   function: clearProcessBlock
        //   function: clearQueue
        //   function: clearConfigData

     mdData = clearMetaDataList( mdData );
     pcbDataPtr = clearProcessBlock( pcbDataPtr );
     clearQueue( &readyQueue );
     clearConfigData( &configDataPtr );
     
    //return success
    return 0;
   }
#endif
