#ifndef MEM_MANAGEMENT_H
#define MEM_MANAGEMENT_H
#include "simController.h"


typedef enum 
            {
             ACCESS_PASS,
             ALLOCATE_PASS,
            }MemoryCodes;


typedef struct MemoryDataType 
     {
      int segId;
      int progId;
      int baseValue;
      int limitValue;
      
      struct MemoryDataType *next;
     } MemoryDataType ;


// function prototypes
int memoryOperation(OpCodeType *tempList, PCB *pcbDataPtr, MemoryDataType **memData, char *timeString );
MemoryDataType *addMemory( MemoryDataType *memDataPtr, OpCodeType *opCodes, PCB procBlock );

int getLimitValue( int memoryValue );
int getBaseValue( int memoryValue );
int getSegId( int memoryValue );

int checkMemoryError( MemoryDataType *memData, PCB *pcbData, OpCodeType *tempList  );
MemoryDataType *eraseMemory( MemoryDataType *memDataPtr );

void displayMemoryError( int memResult );
#endif

