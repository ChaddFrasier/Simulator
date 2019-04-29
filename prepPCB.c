/**
  * @file prepPCB.c
  *
  * @brief This file is used to read and create all the Process Control blocks 
  *           for the simulation OS version 1.2
  *
  * @details Uses the main function to get and print the specified string
  *
  * @version 1.01
  *          <author>863166 (5 October 2018)
  *          First draft of prepPCB file printing functions
  * 
  * @note none
  */

//pre compiler directives
#ifndef PREP_PCB_C
#define PREP_PCB_C
// header files
#include "prepPCB.h"
#include "MetaDataAccess.h"
#include "simtimer.h"

/*
Function Name: loadPCBs()
Algorithm: 
Precondition:
Postcondition:
Exceptions: 
*/

// the metadat in this function will not have the start S
int loadPCBs( OpCodeType *mdData, ConfigDataType *configData, PCB **pcbDataPtr, char *timeString )
   {
    // variable declarations
    int numberOfProgs = 0;
    int returnCode = NO_ERR;
    OpCodeType *tempPtr = mdData;

    // init tempPtr

    // check for end and null of list
    while( tempPtr->next != NULL )
       {
        // check for start of process
        if( tempPtr->opLtr == 'A' && compareString(tempPtr->opName,"start" ) == STR_EQ)
           {

            // This function will only allow 1 PCB becasues i 
            // haven't implimented the second parser part yet
            *pcbDataPtr = createPCB( tempPtr, configData, *pcbDataPtr, numberOfProgs++ );
            
            // opList in PCB is correct here
           }
        // iterate
        tempPtr = tempPtr->next;
        }

    //iterate through temp so data is not messed with 
    accessTimer( 1, timeString);
    //free( tempPtr );   <<<--- LEARN FROM THIS MISTAKE!!!! this free() is deleting the last node of the list, DO NOT DO THIS

    // void return
    return returnCode;
   }

/*
Function Name: getOpCodeList
Algorithm: takes in the dataPtr at the current location, takes all code between A(end)
           stores and returns the data to the new PCB that called it
Precondition: dataPtr must be valid 
Postcondition: is not valid returns NULL else returns the pointer to the new data list
Exceptions:  none
*/
int getOpCodeList(OpCodeType *dataPtr, PCB **destPtr )
   {
    // initalize return pointer
    Boolean processDone = False;
    PCB *tempPCBPtr = *destPtr;
    OpCodeType *tempList = dataPtr;

    while( tempList->next != NULL && !processDone)
       {
        if( ((int)(tempList->opLtr) == (int)'A' && compareString( tempList->opName, "start" ) == STR_EQ) 
            || ( (int)(tempList->opLtr) != (int)'S' && (int)(tempList->opLtr) != (int)'A' ) )

           {
            tempPCBPtr->opCodeList = addNode(tempPCBPtr->opCodeList, tempList); // add copy to the returnPtr
            
            //returns the pointer because PCB is done
           }
        else if( (int)(dataPtr->opLtr) == (int)'A' && compareString( tempList->opName, "end" ) == STR_EQ)

           {
            tempPCBPtr->opCodeList = addNode(tempPCBPtr->opCodeList, tempList); // add copy to the returnPtr
            //tempPCBPtr->opCodeList->next = NULL;
            //displayMetaData( tempPCBPtr->opCodeList);
            //returns the pointer because PCB is done
            processDone = True;
            destPtr = &tempPCBPtr;
            dataPtr = tempList;       
            //free(tempPCBPtr);
            return NO_ERR;
           }
       
        // increment loop 
        tempList = tempList->next;
       }

    return -1;
   }

/*
Function Name: createPCB
Algorithm:  creates a single pcb and adds it to the list of existing pcbs
Precondition: valid meta dat pointer and config pointer as well as the current
              number of programs when this function was called, that will be the
              PCB's unique id
Postcondition: returns the PBC list pointer head
Exceptions: none
*/
PCB *createPCB( OpCodeType *mdData, ConfigDataType *configData, PCB *pcbPtr , int progId )
   { 
    // intialize the returnPtr
    PCB *newPCB = (PCB *)malloc( sizeof(PCB) ); 
       
    //check for first program in data
    if( pcbPtr == NULL)
       {

        // the number of precesses is the new id
        newPCB->progId = progId;

        // init program counter to 0
        newPCB->progCounter = 0;
        
        // get the op code list starting from the A(start)
        getOpCodeList( mdData, &newPCB);
        


        // calculate the runtime of the PCB using the opcode list and all 3 cycle times
        newPCB->progRunTime = getRuntime(newPCB, configData->quantumCycles,
                                       configData->procCycleRate, configData->ioCycleRate );


        // set the state of any new PCB to new
        newPCB->progState = NEW;

        // next is NULL because we havent seen another Process yet
        newPCB->next = NULL;
        
        
        pcbPtr = newPCB;
           
        return pcbPtr;
       }
    else 
       {
        
        // addNodeToPCB()
        // the number of precesses is the new id
        newPCB->progId = progId;

        // init program counter to 0
        newPCB->progCounter = 0;
        
        // get the op code list starting from the A(start)
        getOpCodeList( mdData, &newPCB);


        // calculate the runtime of the PCB using the opcode list and all 3 cycle times
        newPCB->progRunTime = getRuntime(newPCB, configData->quantumCycles,
                                         configData->procCycleRate, configData->ioCycleRate );


        // set the state of any new PCB to new
        newPCB->progState = NEW;

        // next is NULL because we havent seen another Process yet
        newPCB->next = NULL;


        return addPCB( newPCB, pcbPtr );
       }
   }


/*
Function Name: addPCB
Algorithm: loops through the current PCB list and appends the new data onto the end and returns the new pointer
Precondition: localPtr must be valid 
              newPCB should already be loaded with necessary data
Postcondition: if not valid returns NULL else returns the pointer to the new data list
Exceptions:  none

*/
PCB *addPCB( PCB *newPCB, PCB *localPtr )
   {
    if( localPtr == NULL )
       {
        localPtr = newPCB;
        return localPtr;
       }
    localPtr->next = addPCB( newPCB, localPtr->next  );
    return localPtr;
   }
      



/*
Function Name: getRuntime()
Algorithm: retrieves and calculates the total PCB total run time
Precondition: requires getCycles() to decide what value to use for the math
Postcondition: returns the total caluclated runtime of a PCB
Exceptions: none
*/
int getRuntime( PCB *pcbList , int quantum , 
                                         int procCycleTime, int ioCycleTime)
   {
    int totalRunTime = 0;
    OpCodeType *tempList = pcbList->opCodeList;
    // the A(end) will always have a value of 0 because that means EXIT state
    
    if( tempList == NULL )
       {
        return 0;
       }
    else
       {
        while( tempList->next != NULL && compareString(tempList->opName,"end") 
                                                                            != STR_EQ )
           {
            // run the function to get which cycle time to use and do the math
            if( (int)tempList->opLtr != (int)'M' )
               {
                totalRunTime += tempList->opValue * getCycles( tempList->opLtr, procCycleTime , ioCycleTime);
               }
            // next op code
            tempList = tempList->next;
           }
        // return total
        return totalRunTime ;
       }
   }
/*
Function Name: getCycles 
Algorithm: this function was created to distinguish from IO and other 
           operation types and return the proper cycle time for the math function
Precondition: needs a char and the values to decide between
Postcondition: returns int of proper cycle rate
Exceptions: none
 note: UTILITY FOR MATH MUST KEEP 
*/
int getCycles( char opLtr, int procCycleTime, int ioCycleTime)
   {
    switch (opLtr)
       {
        case 'I':
           return ioCycleTime;
        case 'O':
           return ioCycleTime;
        default:
           return procCycleTime;
       }
          
   }


/*
Function Name:
Algorithm:
Precondition:
PostCondition:
Exceptions:
*/
int numberOfPCBs( PCB *localPtr )
   {
    int pcbCount = 0;
    while( localPtr->next != NULL )
       {
        pcbCount++;
        localPtr = localPtr->next;
       }
    return ++pcbCount;
   }


/*
Function Name: removeInnerPCB()
*/



/*
Function Name: clearProcessBlock
Algorithm: this algorithm piggy back off of the clearMetaDataList function 
           because it used an OpCodeList Type checks to see if the PCB ptr is empty
           returns numm if it is null; else clears opList and moves to the next pcb.
           it does this recursivly
Precondition: pcbPtr needs to be accessable
Postcondition: returns null and clears all PCB data
Exceptions: none
* note: version 1.2 :leak fixed here *
*/
PCB *clearProcessBlock(PCB *pcbPtr)
   {

    // check for local pointer not set to null (list not empty)
    if( pcbPtr != NULL )
       {
        if( pcbPtr->next != NULL )
           {    
            pcbPtr->next = clearProcessBlock( pcbPtr->next );
            if( pcbPtr->opCodeList != NULL )
               {
                pcbPtr->opCodeList = clearMetaDataList( pcbPtr->opCodeList );
               }
           }
       }

    return NULL;
   }

#endif
