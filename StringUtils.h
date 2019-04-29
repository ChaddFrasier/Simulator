// Header Information
/**
  * @file StringUtils.h
  *
  * @brief Header file for StringUtils.c Utility program
  *
  * @details Specifies new types, global constants and Utility 
  *          programs for the StringUtils.c Utility file
  *
  * @version 1.01
  *          863166 (14 September 2018)
  *          First major draft of Utility file
  *
  * @note none
  */

//Pre-compiler directive
#ifndef STRING_UTILS_H
#define STRING_UTILS_H

//Header Files
#include <stdio.h> // file operations
#include <stdlib.h>// dynamic memory ops

// Global Extern Constants
typedef enum { False, True } Boolean;
typedef enum { NO_ERR,
               INCOMPLETE_FILE_ERR,
               INPUT_BUFFER_OVERRUN_ERR } StringManipCode;

extern const int MAX_STR_LEN;
extern const int STD_STR_LEN;
extern const int SUBSTRING_NOT_FOUND;
extern const int STR_EQ;
extern const char SPACE;
extern const char NULL_CHAR;
extern const char COLON;
extern const char PERIOD;
extern const char SEMICOLON;
extern const char LEFT_PAREN;
extern const char RIGHT_PAREN;
extern const Boolean IGNORE_LEADING_WS;
extern const Boolean ACCEPT_LEADING_WS;

//Function Prototype
int getStringLength     ( char *teststr );
int findSubString       ( char *testStr, char *searchSubStr );
int compareString       ( char *oneStr, char *otherStr );
void copyString         ( char *destination, char *source );
void concatString       ( char *destination, char *source );
void setStrToLowerCase  ( char *destStr, char *sourceStr );
void getSubString       ( char *destStr, char *sourceStr, int startIndex, 
                                                            int endIndex );
Boolean isEndOfFile     ( FILE *filePtr );
char setCharToLowerCase ( char testChar );
char getLineTo          ( FILE *filePtr, int bufferSize, char stopChar, 
                              char *buffer, Boolean omitLeadingWhiteSpace);
#endif
