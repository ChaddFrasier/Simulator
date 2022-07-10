#include "simController.h"
//precomplier directives
#ifndef SYS_LOG_H
#define SYS_LOG_H

// type definition
typedef enum {
              STARTER_CODE,
              UPLOAD_CONFIG_CODE,
              UPLOAD_META_CODE,
              SIM_BEGIN_CODE,
              SIM_END_CODE
             } LogCodes;


// function prototypes
void SystemLogPrint( int commandMsg, int logToCode, char *timeString, char *fileName ); // does a check and performs entire log action

void StarterLog( int code,  int logToCode, char *fileName ); // this will perform both system log/ print for startups

void logProgramIndicators( int commandMsg, int logToCode, char *timeString ,
                           int progId, int progRunTime, char *fileName); // this will do both print and log 
//void displayProgramSelect( int commandMsg, char *timeString , int progId, int progRunTime );

void logInternalString( int commandMsg, int logToCode, char *timeString , int progId, char *nameString,
                                         char *startEndString, char *fileName );

void displayInternalString( int commandMsg, char *timeString , int progId, char *nameString, char *startEndString );
int getCommand( char commandMsg);
void getOpLetterString( OpCodeType opCode, char **resultString );
void logMemString( int commandMsg, int logToCode, char *timeString , int progId, char *nameString,
                                         char *startEndString, char *fileName, int segNum, int baseNum, int limitNum );

#endif
