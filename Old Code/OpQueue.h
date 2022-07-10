// precompiler directives
#ifndef OP_QUEUE_H
#define OP_QUEUE_H

// imported packages
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "StringUtils.h"
#include "prepPCB.h"


// global constants

// type definitions
typedef struct QueueObj {
                         int front, rear, size;
                         unsigned capacity;
                         int* array;
                  }QueueObj; 


// NOTE FOR FUTURE PROJECTS: 
//   For this queue object I will be able to add priority to it 
//     by making sure the Nodes have a priority system that the 
//     queue can detect with a new functions that I will eventually 
//     call getHighestPriority()

// prototype functions
int isFull( struct QueueObj* queue );
QueueObj *createQueue( unsigned capacity );
int isEmpty( struct QueueObj* queue );
void enqueue( struct QueueObj* queue, int item );
int dequeue( struct QueueObj* queue);
int front(struct QueueObj* queue);
int rear(struct QueueObj* queue);
void clearQueue( QueueObj **queuePtr );

QueueObj *getNextShortest( QueueObj **localQueue, PCB *pcbData );
int inQueue( int progId, QueueObj *tempQueue);

#endif
// 
