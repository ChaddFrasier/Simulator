// Header Information
/**
  * @file OpQueue.c
  *
  * @brief main driver file for the simulation
  *
  * @details collects data from a config file, and then stores the data 
  *              in a data structure for later 
  *
  * @version 1.01
  *         863166 (8 October 2018)
  *         First major draft of a basic integer queue
  * 
  * @note Requires OpQueue.h
  */


// precompiler directives
#ifndef OP_QUEUE_C
#define OP_QUEUE_C

#include "OpQueue.h"

/* 
Function Name: createQueue
Algorithm: creates a queue object from an unsigned and returns a pointer to the queue
Preconditon: Have a valid pointer to pass return to
Postcondition: creates and returns pointer, pointer array is empty
Exceptions: None
*/
QueueObj *createQueue( unsigned capacity)
   {
    // create queue object

    QueueObj *tempQueue = (struct QueueObj*) malloc(sizeof(struct QueueObj));

    tempQueue->capacity = capacity;
    tempQueue->front = 0;
    tempQueue->size = 0;
    tempQueue->rear = capacity-1;
    tempQueue->array = (int *)malloc(tempQueue->capacity * sizeof(int*));

    return tempQueue;
   }

/* 
Function Name: isFull
Algorithm: checks to see if the queueobject is full
            by comparing the current size and the total memory in array
Preconditions: a queue object needs to be valid 
Postcondition: return boolean value, True if the queue is full
Exceptions:none
*/
int isFull( struct QueueObj* queue )
   {
    return (queue->size == queue->capacity);
   } 


/* 
Function Name: isEmpty
Algorithm: checks to see if the queueobject is empty
            by comparing the current size and the total memory slots
Preconditions: a queue object needs to be valid 
Postcondition: return boolean value, True if the queue is empty
Exceptions:none
*/
/* RETURNS A BOOL: convert this later*/
int isEmpty( struct QueueObj* queue )
   {
    return (queue->size == 0);
   }

/* 
Function Name: enqueue()
Algorithm: checks to see if the queueobject is full then adds 
            the item given to the queue array, also increment size count
Preconditions: a queue object needs to be valid and an int (program Id)needs to be passed
Postcondition: return boolean value, True if the queue is full
Exceptions:none
*/
void enqueue( struct QueueObj* queue, int item )
   {
    // if the queue is full stop the function
    if( isFull( queue ) )
       {
        return;
       }
    // set the rear to the next slot in the queue array using pointer addition
    queue->rear = (queue->rear + 1)%queue->capacity;
    // add the item to the end of the queue
    queue->array[queue->rear] = item;
    // keep track of the total queue size
    queue->size = queue->size + 1;
   }


/* 
Function Name: dequeue
Algorithm: checks to see if the queueobject is empty
            then pulls off the front and points the front to the next slot
Preconditions: a queue object needs to be valid 
Postcondition: return the int in front
Exceptions:none
*/
int dequeue( QueueObj *queue )
   {
    // if the queue is empty then we cant dequeue return error value
    if( isEmpty( queue ) )
       {
        return INT_MIN;
       }
    // init the item to return
    int item = queue->array[queue->front];
    // set the front equal to the next value in the list (not in the queue)
    queue->front = (queue->front + 1)%queue->capacity;
    // decrease the size of the queue
    queue->size = queue->size - 1;
    return item;
   }


/* 
Function Name: front()
Algorithm: checks to see if the queueobject is empty
            returns a negative if empty; returns the front value
Preconditions: a queue object needs to be valid 
Postcondition: return boolean value, True if the queue is full
Exceptions:none
*/
int front(QueueObj *queue)
   {
    if( isEmpty( queue ) )
       {
        return INT_MIN;
       }
    return queue->array[queue->front];
   }


/* 
Function Name: rear()
Algorithm: checks to see if the queueobject is empty
            returns negative if empty; returns the last peice in the queue
Preconditions: a queue object needs to be valid 
Postcondition: return boolean value, True if the queue is full
Exceptions:none
*/
int rear( QueueObj *queue )
   {
    if( isEmpty( queue ) )
       {
        return INT_MIN;
       }
    return queue->array[queue->rear];

   }




/*
Function Name:
Algorithm:
Precondition:
Postcondition:
Exceptions:
*/

QueueObj *getNextShortest( QueueObj **localQueue, PCB *pcbData )
   {
    
    
    QueueObj *tempQueue = *localQueue;

    for( int index = 0; index < numberOfPCBs( pcbData ); index++ )
       {
        PCB shortestPCB = *pcbData;
        PCB *tempPtr = pcbData;

        while( tempPtr->next != NULL )
           {
            if( (tempPtr->progRunTime < shortestPCB.progRunTime && 
                       tempPtr->progRunTime != 0 && !inQueue( tempPtr->progId, tempQueue))
                      || inQueue( shortestPCB.progId, tempQueue) )
               {
                shortestPCB = *tempPtr;
               }
            tempPtr = tempPtr->next;
           }
        if( (tempPtr->progRunTime < shortestPCB.progRunTime && !inQueue( tempPtr->progId, tempQueue ))
             || inQueue( shortestPCB.progId, tempQueue) )
 
           {    
            enqueue( tempQueue, tempPtr->progId );
            //printf("rear middle: %d\n", rear( tempQueue ));
           }
        else if( !inQueue( shortestPCB.progId, tempQueue ) )
           {
            enqueue( tempQueue, shortestPCB.progId );
            //printf("rear end: %d\n", rear( tempQueue ));
           } 
       }
    localQueue = &tempQueue;    

    return *localQueue;
   }




/**/
int inQueue( int progId, QueueObj *tempQueue)
  {
   for( int index = 0; index < tempQueue->size; index++ )
      {
       if( tempQueue->array[index] == progId )
          {
           return True;
          }
      }
   return False;
  }







/* 
Function Name:  clearQueue()
Algorithm: checks to see if the queueobject is empty
            then checks if the queue array is empty
            clears any malloc data left
Preconditions: a queue object needs to be valid 
Postcondition: return boolean value, True if the queue is full
Exceptions:none
*/
void clearQueue( QueueObj **queue )
   {
    if( *queue != NULL )
       {
        if( (*queue)->array != NULL )
           {
            free( (*queue)->array );     
           }
        free( *queue );
       }
   }

#endif
