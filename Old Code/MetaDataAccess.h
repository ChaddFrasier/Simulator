// Header Information
/**
  * @file MetaDataAccess.h
  *
  * @brief Header file for MetaDataAccess.c data upload program
  *
  * @details Specifies new types, global constants and Utility 
  *          programs for the MetaDataAccess.c Utility file
  *
  * @version 1.01
  *          863166 (14 September 2018)
  *          First draft of metadata upload functions
  *
  * @note none
  */

//Pre-complier directive
#ifndef META_DATA_ACCESS_H
#define META_DATA_ACCESS_H

//header file
#include "StringUtils.h"

// global constants
typedef enum { MD_FILE_ACCESS_ERR = 3,
               MD_CORRUPT_DESCRIPTOR_ERR,
               OPCMD_ACCESS_ERR,
               CORRUPT_OPCMD_LETTER_ERR,
               CORRUPT_OPCMD_NAME_ERR,
               CORRUPT_OPCMD_VALUE_ERR,
               UNBALENCED_START_END_ERR,
               COMPLETE_OPCMD_FOUND_MSG,
               LAST_OPCMD_FOUND_MSG, 
               PCB_ORDERING_ERR,
               SEG_FAULT_ERR } OpCodeMessages;

   //Op code type
typedef struct OpCodeType
   {
    char opLtr;
    char opName[100]; // name length max is 99 plus '\0'
    int opValue;

    struct OpCodeType *next;
   } OpCodeType;

//function prototype
int getOpCodes( char *fileName, OpCodeType **opCodeDataHead );
int updateStartCount( int count, char *opString );
int updateEndCount( int count, char *opString );
int getOpCommand( FILE *filelPtr, OpCodeType *inData );
void displayMetaData( OpCodeType *localPtr );
void displayMetaDataError( int code );
Boolean isDigit( char testChar );
Boolean checkOpString( char *testStr );
OpCodeType *clearMetaDataList( OpCodeType *localPtr );
OpCodeType *addNode( OpCodeType *localPtr, OpCodeType *newNode );

#endif
