/**
 * @file SimpleTimer.h
 *
 * @brief Header file for micro-second precision timer
 * 
 * @author Michael Leverington
 * 
 * @details Specifies all member methods of the SimpleTimer
 *
 * @version 2.00 (13 January 2017)
 *          1.00 (11 September 2015)
 *
 * @Note None
 */

#ifndef SIMTIMER_H
#define SIMTIMER_H

#include <sys/time.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>

enum TIMER_CTRL_CODES { ZERO_TIMER, LAP_TIMER, STOP_TIMER };

typedef enum { FORK_FAIL_ERR } THREAD_ERR_CODES;
typedef enum { False, True } Boolean;

extern const char RADIX_POINT;
extern const char SPACE;

void runTimer( int milliSeconds );
double accessTimer( int controlCode, char *timeStr );
double processTime( double startSec, double endSec, 
                           double startUSec, double endUSec, char *timeStr );
void timeToString( int secTime, int uSecTime, char *timeStr );

#endif
