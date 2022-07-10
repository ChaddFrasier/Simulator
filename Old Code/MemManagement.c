#ifndef MEM_MANAGEMENT_C
#define MEM_MANAGEMENT_C

#include "simController.h"


int memoryOperation(OpCodeType *tempList, PCB *pcbDataPtr, MemoryDataType **memData, char *timeString )
   {
    
    // this function will take in the memdata structure and parse the whole thing
      // if its an allocate operation it will check if this area exists already in the structure
           // else return seg fault
     // if it is an access operation we check to see if that memory block belongs to the current process
        // if it belongs to another processes or is not there: then seg fault
    MemoryDataType *tempMemData = *memData;
    // check to see if this memory currently overlaps with 
    int memResult = checkMemoryError( tempMemData, pcbDataPtr, tempList  );
    
    if( memResult == ALLOCATE_PASS)
       {
        *memData = addMemory( tempMemData, tempList, *pcbDataPtr);
       }
    else if( memResult == ACCESS_PASS )
       {
        /* TODO: 
                Scan the now working memory block list and perform 
                arithmetic similar to the add to determine if:

                1. the the segId exists in the list
                2. the correct pcb is accessing it
                3. make sure the base is in bound and the limit does not overrun the block.
                
            */
       }
    else if( memResult == SEG_FAULT_ERR )
       {
        return SEG_FAULT_ERR;
       }
    
    /*
    printf("Whole Memory Address : %d\n", tempList->opValue );
    printf("The first node added segId  : %d\n", memData->segId );
    printf("The first node added ProgId : %d\n", memData->progId );
    printf("The first node added Base Val : %d\n", memData->baseValue );
    printf("The first node added Limit Val : %d\n", memData->limitValue );
    */
    memData = &tempMemData;
    return NO_ERR;
   }


/* TODO: needs to check the configFile memory size*/


int checkMemoryError( MemoryDataType *memData, PCB *pcbData, OpCodeType *localList  )
   {
    OpCodeType *tempList = localList;
    MemoryDataType *tempMemPtr = memData;
    
    if( memData == NULL && compareString("allocate", tempList->opName) == STR_EQ )
       {
        return ALLOCATE_PASS;
       }
    
    else if( memData == NULL && compareString("access", tempList->opName) == STR_EQ )
       {
        printf("This segfault occurs from an emnpty access" );
        return SEG_FAULT_ERR;
       }

    if( tempMemPtr != NULL && compareString("allocate", tempList->opName) == STR_EQ )
       {
        // runs if there is more than 1 memory block in the process
        while( tempMemPtr->next != NULL )
           {
            int testBase = tempMemPtr->baseValue;
            int basePlusLimit = tempMemPtr->limitValue + testBase;

            if( tempMemPtr->segId != getSegId(tempList->opValue) )
               {
                if( getBaseValue(tempList->opValue) >= testBase && getBaseValue(tempList->opValue) <= basePlusLimit)
                   {
                    return SEG_FAULT_ERR;
                   }
                if( (getBaseValue(tempList->opValue ) + getLimitValue(tempList->opValue )) >= testBase &&
                  (getBaseValue(tempList->opValue ) + getLimitValue(tempList->opValue )) <= basePlusLimit )
                   {
                    return SEG_FAULT_ERR;
                   }
               }

            tempMemPtr = tempMemPtr->next;
           }

        int testBase = tempMemPtr->baseValue;
        int basePlusLimit = tempMemPtr->limitValue + testBase;

        // runs if there is only 1 memory block in the list
printf("testBase: %d, basePlusLimit: %d\n", tempMemPtr->baseValue, tempMemPtr->baseValue + tempMemPtr->limitValue);        
        if( tempMemPtr != NULL && tempMemPtr->segId != getSegId(tempList->opValue) )
           {
            if( (getBaseValue(tempList->opValue) >= testBase && getBaseValue(tempList->opValue) <= basePlusLimit))
               {
                return SEG_FAULT_ERR;
               }
            if( (getBaseValue(tempList->opValue ) + getLimitValue(tempList->opValue )) >= testBase &&
               (getBaseValue(tempList->opValue ) + getLimitValue(tempList->opValue )) <= basePlusLimit )
               {
                return SEG_FAULT_ERR;
               }
           }
        return ALLOCATE_PASS;
       }
    else if( compareString("access", tempList->opName) == STR_EQ )
       {
        return ACCESS_PASS;
       }
    return ALLOCATE_PASS;   
   }


MemoryDataType *addMemory( MemoryDataType *memData, OpCodeType *opCodes, PCB procBlock )
   {
    
    if( memData == NULL)
       {
        memData = (MemoryDataType *)malloc( sizeof( MemoryDataType ));

        memData->segId = getSegId( opCodes->opValue );
        memData->progId = procBlock.progId;
        memData->baseValue = getBaseValue( opCodes->opValue );
        memData->limitValue = getLimitValue( opCodes->opValue );
        memData->next = NULL;
       }
    else
       {
        MemoryDataType *tempMem = memData;
        MemoryDataType *newMemData = (MemoryDataType *)malloc( sizeof( MemoryDataType ));

        newMemData->segId = getSegId( opCodes->opValue );
        newMemData->progId = procBlock.progId;
        newMemData->baseValue = getBaseValue( opCodes->opValue );
        newMemData->limitValue = getLimitValue( opCodes->opValue );
        newMemData->next = NULL;

        while( tempMem->next != NULL )
           {
            tempMem = tempMem->next;
           }
        tempMem->next = newMemData;
        printf( "add this bitch: %d\n",newMemData->segId );
        printf( "to this bitch: %d\n",tempMem->segId ); 
        memData = tempMem;
       }

    return memData;
   } 


int getLimitValue( int memoryValue )
   {
    return (memoryValue%1000);
   }


int getBaseValue( int memoryValue )
   {
    return ((memoryValue%1000000)/1000);
   }


int getSegId( int memoryValue )
   {
    return (memoryValue/1000000);
   }



void displayMemoryError( int memResult )
   {
    switch( memResult )
       {
      
        case SEG_FAULT_ERR:
            printf("Segmentation Fault\n");
            printf("Aborting Process\n"); 
       }
   }



MemoryDataType *eraseMemory( MemoryDataType *memDataPtr )
   {
    if( memDataPtr != NULL )
       {
        if( memDataPtr->next != NULL )
           {
            eraseMemory( memDataPtr );
           }
        free( memDataPtr );
       }
    return NULL;
   }

#endif
