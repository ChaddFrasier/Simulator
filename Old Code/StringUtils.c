// Header Information
/**
  * @file StringUtils.c
  *
  * @brief Utility file for string manipulation
  *
  * @details sets global constants and lays out all functions
  *           that are vital to string manipulation
  *
  * @version 1.01
  *          863166 (14 September 2018)
  *          First major draft of Utility file
  *
  * @note Requires StringUtils.h
  */

//Pre-compiler directive
#ifndef STRING_UTILS_C
#define STRING_UTILS_C

// Header Files
#include "StringUtils.h"

// global constants
const int MAX_STR_LEN = 200;
const int STD_STR_LEN = 80;
const char NULL_CHAR = '\0'; // null character
const int SUBSTRING_NOT_FOUND = -404;
const int STR_EQ = 0;
const char SPACE = ' ';
const char COLON = ':';
const char SEMICOLON = ';';
const char LEFT_PAREN = '(';
const char RIGHT_PAREN = ')';
const char PERIOD = '.';
const Boolean IGNORE_LEADING_WS = True;
const Boolean ACCEPT_LEADING_WS = False;

/*
Function Name: getStringLength
Algorithm: finds the length of a string up the the null character
Precondition: given C-style with null character at end
PostCondition: returns number of characters from the 
               beginnng up to the null character
Exceptions: none
Note: loop will run, number of character in the string, times
*/
int getStringLength(char *testStr)
   {
    // initalize function/varables
    int index = 0;

    // loop up to null or limit
    while( index < MAX_STR_LEN && testStr[ index ] != NULL_CHAR )
       {
        // increment the counter index
        index++;
       }

    //end loop
    //return the counter index value
    return index;
   }

/*
Function Name: copyString
Algorithm: Copies content of one string into another
PreCondition: Given C-Style source string, having a null '\0'
              at the end of string; destination string is passed
              in as a perameter with enough memory to store the source.
PostCondition: Destination String is the same as the source string
Exceptions: none
Note: limit test loop to maximum character for safety
*/
void copyString( char *destination, char *source )
   {
    // initialize  function/ variables
    int index = 0;

    // loop until null character is found in source string
    // loop limit to MAX_STR_LEN
    while( index < MAX_STR_LEN && source[ index ] != NULL_CHAR )
       {
        // assign source character to destination element
        destination[ index ] = source[ index ];

        // increment index
        index++;

        // assign null character to next destination element
        destination[ index ] = NULL_CHAR;
       }
    // end loop
   }

/*
Function Name: concatString
Algorithm: Combines both strings into the destination
PreCondition: Given C-Style source string, having a null '\0'
              at the end of string; destination string is passed
              in as a perameter with enough memory to store the 
              source and itself.
PostCondition: Destination String is itself with the source added
               to the end
Exceptions: none
Note: limit test loop to maximum character for safety
*/
void concatString( char *destination, char *source )
   {
    // initialize function/variables
    // set desination index to length of destination string
    int destIndex = getStringLength( destination );

    // set source index to zero
    int sourceIndex = 0;

    // loop to end of source index (null character)
    // loop limit to MAX_STR_LEN
    while( sourceIndex < MAX_STR_LEN && source[ sourceIndex ] != NULL_CHAR )
       {
        // assign source character to destination at destination index
        destination[ destIndex ] = source[ sourceIndex ];

        // increment source and destination indecies
        sourceIndex++; destIndex++;

        // assign null character to next destination element
        destination[ destIndex ] = NULL_CHAR;
       }
    // end loop
   }

/*
Function Name: compareString
Algorithm: Compares two strings alphabetically such that:
                   if oneStr < otherStr, the function returns a value < 0
                   if oneStr > otherStr, the function returns a value > 0
                   if oneStr == otherStr, the function returns 0
                   if two strings are identical up to the point that one 
                   is longer,the difference in length will be returned
PreCondition: Given two C-Style source strings, having a null '\0'
              at the end of both strings;
PostCondition: int returned as specified above
Exceptions: none
Note: limit test loop to maximum character for safety
*/
int compareString( char *oneStr, char *otherStr )
   {
    // initialize function/variables
    int index = 0, difference;

    // loop to end of one of the two strings
    // loop limited to MAX_STR_LEN
    while( index < MAX_STR_LEN && oneStr [ index ] != NULL_CHAR 
                                  && otherStr[ index ] != NULL_CHAR )
       {
        // find the difference between the currently alighned characters
        difference = oneStr[ index ] - otherStr[ index ];

        // check for non-zero difference
        if( difference != 0 )
           {
             // return non-zero difference
             return difference;
           }

        // increment index
        index++;
       }
    //end loop
    // assume strings are equal at this point, return string length difference
       //function getStringLength
    return getStringLength( oneStr ) - getStringLength( otherStr );
   }

/*
Function Name: getSubString
Algorithm: captures sub string eithin a larger string between 
           two inclusive indices
PreCondition: Given C-Style source string having a null '\0'.
              and another peratether that can hold the resulting string
PostCondition: substring is returned as a perameter
Exceptions: empty string returned if any of the index parameters are 
            out of range
Note: copy of source string is made internally to protect from aliasing
*/
void getSubString( char *destStr, char *sourceStr, 
                                  int startIndex, int endIndex )
   {
    //initialize function/variables
       // set length of source string
       int sourceStrLen = getStringLength ( sourceStr );

       // initialize destination index to 0
       int destIndex = 0;

       // initialize the source index to start index perameter
       int sourceIndex = startIndex;

       // create pointer to temp string
       char *tempSourceStr;

    // check for indices within limits
    if( startIndex >= 0 && startIndex <= endIndex && endIndex < sourceStrLen )
       {
        // create temporary string, copy sourcestring to it
           //function: malloc, copyString
        tempSourceStr = (char *) malloc( sourceStrLen + 1 );
        copyString( tempSourceStr, sourceStr );

    // loop across requested substring (indeces)
        while( sourceIndex <= endIndex )
           {
            // assign source character to destinationm element
            destStr[ destIndex ] = tempSourceStr[ sourceIndex ];

            // increment indices
            destIndex++; sourceIndex++;

            // add null character to next destination element
            destStr[ destIndex ] = NULL_CHAR;
           }
       // end loop
    // release memory used for temp source string
       // function: free
       free( tempSourceStr );
      }
    // otherwise, assume indices not in limits
    else
       {
        // create empty string null character
        destStr[0] = NULL_CHAR;
       }
   }

/*
Function Name: findSubString
Algorithm: linear search for a given substring inside a given test string
PreCondition: Given two C-Style source strings having a null '\0' at
              the end of both of the strings
PostCondition: index of the substring location returned,
               or SUBSTRING_NOT_FOUND constant is returned.
Exceptions: empty string returned if any of the index parameters are
            out of range
Note: copy of source string is made internally to protect from aliasing
*/
int findSubString( char *testStr, char *searchSubStr )
   {
    // initialize function/ variables
       // initialize test string length
            // function: getStringLength
       int testStrLen = getStringLength( testStr );

       // initialize master index- location of sub string start point
       int masterIndex = 0;

       // initialize other varibales
       int searchIndex, internalIndex;

    // loop across the test string
    while( masterIndex < testStrLen )
       {
         // set internal loop index to current test string index
         internalIndex = masterIndex;

         // set internal search index to 0
         searchIndex = 0;

         // loop to end of test string
         //    while test string/substring characters are the same
         while( internalIndex <= testStrLen 
                 && testStr[ internalIndex ] == searchSubStr[ searchIndex ] )
            {
             // increment test string, substring indices
             internalIndex++; searchIndex++;

             // check for end of substring (search complete)
             if( searchSubStr[ searchIndex ] == NULL_CHAR )
               {
                 //return current test string index 
                return masterIndex;
               }
            }
           // end loop
         // increment current test string index
         masterIndex++;

         //end loop
        }
    // assume tests have failed at this point, return SUBSTRING_NOT_FOUND
    // temp return
    return SUBSTRING_NOT_FOUND;
   }

/*
Function Name: setStrToLowerCase
Algorithm: iterates through string, set all upper case letters to lower case
           without changing any other characters
PreCondition: Given a C-Style source string having a null '\0' at
              the end of string, and a destination string is passed 
              as a perameter with enough memory to hold the lower case string
PostCondition: All upper case letters in the source string are changed 
               to lower case in the destination string
Exceptions: limit on string loop in case of incorrect string format
Note: copy of source string is made internally to protect from aliasing
*/
void setStrToLowerCase( char *destStr, char *sourceStr )
   {
    // initialize function/variables
       // initialize source string index to 0
    int index = 0;

    //create temporary source string
       //function: getStringLength, malloc
    int tempStrLen = getStringLength( sourceStr );
    char *tempSourceStr = (char *) malloc( tempStrLen + 1 );

    // copy source string to temporary string
    copyString( tempSourceStr, sourceStr );

    // loop limited to MAX_STR_LEN
    while( tempStrLen < MAX_STR_LEN 
             && tempSourceStr[ index ] != NULL_CHAR)
       {
         //change letter to lower case as needed and assign
         //   to destination string
            // function: setCharToLowerCase
         destStr[ index ] = setCharToLowerCase( tempSourceStr[ index ] );

         // increment index
         index++;
         destStr[ index ] = NULL_CHAR;
       }
       // end loop

    // release temp string
       // function: free 
    free( tempSourceStr );
    // no return
   }

/*
Function Name: setCharToLowerCase
Algorithm: test character perameter for upper case, change it to lower case,
           makes no changes to lower case letters
PreCondition: given character value
PostCondition: upper case letter is set to lower case,
               otherwise, character is returned unchanged
Exceptions: none
Note: none
*/
char setCharToLowerCase( char testChar )
   {
    // initialize function/variables
       //none
    // check for character between 'A' and 'Z' inclusive
    if( testChar >= 'A' && testChar <= 'Z' )
      {
       // convert upper to lower case
       testChar = (char) (testChar - 'A' + 'a');
      }
    // temp return
    return testChar;
   }

/*
Function Name: getLineTo
Algorithm: finds given text in a file, skipping white space if specified,
           stops searching at a given character ot length
PreCondition: file is open with valid file pointer;
              char buffer has adequate memory for data;
               stop character and length are valid
PostCondition: ignores leading white space if specified;
               captures all printable characters and stored in string buffer;
Exceptions: returns INCOMPLETE_FILE_ERR if no valid data found;
            returns NO_ERR if successful operation
Note: none
*/
char getLineTo( FILE *filePtr, int bufferSize, char stopChar, 
                                  char *buffer, Boolean omitLeadingWhiteSpace)
   {
    // initialize function/variables

       //initialize character index
       int charIndex = 0;

       //initialize status return to NO_ERR
       int statusReturn = NO_ERR;

       //initialize buffer size available flag to true
       Boolean bufferSizeAvailable = True;

       //initialize other variables
       int charAsInt;
 
    // get the first character
       // function: fgetc
    charAsInt = fgetc( filePtr );

    // use a loop to consume leading white space, if flagged
    while( omitLeadingWhiteSpace == True
            && charAsInt != (int) stopChar
               && charIndex < bufferSize
                  && charAsInt <= (int) SPACE )
        {
         // get next char as int
            // function: fgetc
         charAsInt = fgetc( filePtr );
        }
         // end loop

    //capture string
    //loop while character is not stop character and buffer size is available
    while( charAsInt != stopChar && bufferSizeAvailable == True )
        {
         //check for input failure
         // function: isEndOfFile
         if( isEndOfFile( filePtr ) == True )
            {
             //return incomplete file error
             return INCOMPLETE_FILE_ERR;
            }

         // check for usable (printable) character
         if( charAsInt >= (int) SPACE ) 
            {
             // assign input character to buffer string
             buffer[ charIndex ] = (char) charAsInt;

             // increment index
             charIndex++;
            }

          // set next buffer element to null character
         buffer[ charIndex ] = NULL_CHAR;

         // check for not at end of buffer size
         if( charIndex < bufferSize - 1 )
            {
             // get new character
             charAsInt = fgetc( filePtr );
            }
           // otherwise, assume end of buffer size
         else
            {
             // set buffer size Boolean to false to end loop
             bufferSizeAvailable = False;
             // set status return to buffer overrun error
             statusReturn = INPUT_BUFFER_OVERRUN_ERR;
            }
        }
    // end loop
    // return data
    return statusReturn;
   }

/*
Function Name: isEndOfFile
Algorithm: reports end of file, using feof
PreCondition: file is open with valid file ptr
PostCondition: reports end of file
Exceptions: none
Note: none
*/
Boolean isEndOfFile( FILE *filePtr )
   {
    // initialize function/variables
    // check for feof end of file response
          // function: feof
    if( feof( filePtr ) != 0 )
       {
        // temp return
        return True;
       }
    // Otherwise, Assume test failed at this point,return false
    return False;
   }
#endif
