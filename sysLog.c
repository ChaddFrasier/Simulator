/**
  * @file sysLog.c
  *
  * @brief This file is used to print to the file line by line for the 
  *           simulation OS version 1.2
  *
  * @details Uses the main function to get and print the specified string
  *
  * @version 1.01
  *          <author>863166 (5 October 2018)
  *          First draft of sysLog file printing functions
  * 
  * @note none
  */

//precomplier directives
#ifndef SYS_LOG_C
#define SYS_LOG_C

//header file
#include "simController.h"



/*
Function Name: logInternalString()
Algorithm: takes a commandMsg from the sim along with all relevent data to print ot file
Precondition: requires a valid file string to operate, also 
               needs requested data for string
Postcondition: prints 1 line of the file
Exceptions: none
*/
void logMemString( int commandMsg, int logToCode, char *timeString , int progId, char *nameString,
                                         char *startEndString, char *fileName, int segNum, int baseNum, int limitNum )
   {
    // declare file pointer
    FILE *filePtr;
     // open file for append    
    filePtr = fopen(fileName, "a+");
    // check for file open failure
     if( logToCode != LOGTO_MONITOR_CODE )
        {
         if( filePtr != NULL )
         {
          // switch on messege
          switch(commandMsg)
             {
              // Memory operation
              case PROCESS_MEMORY_CODE:
                  if( compareString( startEndString, "end") != STR_EQ )
                     {
                      // print line
                      fprintf(filePtr,"%s, OS: Process %d,  MMU  attempt to %s %d/%d/%d\n", timeString, 
                                        progId, nameString, segNum, baseNum, limitNum );
                      // close file
                      fclose(filePtr);
                      // stop case
                      break;

                     }
                  else
                     {
                      fprintf( filePtr, "%s, OS: Process %d,  MMU  succesful %s \n", timeString, progId ,nameString);
                      // close file
                      fclose(filePtr);
                      // stop case
                      break;
                     }
                  break;              
              default:
                  fclose( filePtr );
                  break;
             }
         }

       }
    if( logToCode != LOGTO_FILE_CODE )
       {     
        switch(commandMsg)
            {
             case PROCESS_MEMORY_CODE:
                 if( compareString( startEndString, "end") != STR_EQ )
                    {
                     printf("%s, OS: Process %d,  MMU  attempt to %s %d/%d/%d\n", timeString, 
                                        progId, nameString, segNum, baseNum, limitNum );
                    }
                 else
                    {
                     printf("%s, OS: Process %d,  MMU  succesful %s \n", timeString, progId ,nameString);
                    }
                 break;
              
            } 
      }
   }





/*
Function Name: logInternalString()
Algorithm: takes a commandMsg from the sim along with all relevent data to print ot file
Precondition: requires a valid file string to operate, also 
               needs requested data for string
Postcondition: prints 1 line of the file
Exceptions: none
*/
void logInternalString( int commandMsg, int logToCode, char *timeString , int progId, char *nameString,
                                         char *startEndString, char *fileName )
   {
    // declare file pointer
    FILE *filePtr;
     // open file for append    
    filePtr = fopen(fileName, "a+");
    // check for file open failure
     if( logToCode != LOGTO_MONITOR_CODE )
        {
         if( filePtr != NULL )
         {
          // switch on messege
          switch(commandMsg)
             {
              // output process
              case PROCESS_OUTPUT_CODE:
                  // print line
                  fprintf(filePtr, "%s, OS: Process %d,  %s %s %s\n", timeString, progId, nameString, "output", startEndString );
                  // close file
                  fclose(filePtr);
                  // stop case
                  break;

              // input process
              case PROCESS_INPUT_CODE:
                  // print line
                  fprintf(filePtr,"%s, OS: Process %d,  %s %s %s\n", timeString, progId, nameString, "input", startEndString );
                  // close file
                  fclose(filePtr);
                  // stop case
                  break;
              // run operation
              case PROCESS_RUN_CODE:
                  // print line
                  fprintf(filePtr,"%s, OS: Process %d,  %s %s %s\n", timeString, progId, nameString, "operation", startEndString );
                  // close file
                  fclose(filePtr);
                  // stop case
                  break;
              default:
                  fclose( filePtr );
                  break;
             }
         }

       }
    if( logToCode != LOGTO_FILE_CODE )
           {     
            switch(commandMsg)
               {
                case PROCESS_OUTPUT_CODE:
                    printf("%s, OS: Process %d,  %s %s %s\n", timeString, progId, nameString, "output", startEndString );
                    break;
                case PROCESS_INPUT_CODE:
                    printf("%s, OS: Process %d,  %s %s %s\n", timeString, progId, nameString, "input", startEndString );
                    break;
                case PROCESS_RUN_CODE:
                    printf("%s, OS: Process %d,  %s %s %s\n", timeString, progId, nameString, "operation", startEndString );
                    break;
               } 
           }
     }


/*
Function Name: logProgramIndicators()
Algorithm: takes a commandMsg from the sim along with all relevent data to print ot file
Precondition: requires a valid file string to operate, also 
               needs requested data for string
Postcondition: prints 1 line of the file
Exceptions: none
*/

void logProgramIndicators( int commandMsg, int logToCode, char *timeString , int progId, int progRunTime, char *fileName )
   {
    // declare file pointer 
    FILE *filePtr;
    // open for append
    filePtr = fopen(fileName, "a+");
     // check for failure   
    if( filePtr != NULL && logToCode != LOGTO_MONITOR_CODE)
       {
        // switch on messege
        switch(commandMsg)
           {
            // system process selected
            case SYSTEM_PROC_SELECT_CODE:
                // print line
                fprintf(filePtr,"\n%s, OS: Process %d was selected with %d ms, remaining\n", timeString, progId, progRunTime );
                // close file
                fclose(filePtr);
                // stop case
                break;

            // system process selected
            case SYSTEM_PROC_RUN_CODE:
                // print line
                fprintf(filePtr, "%s, OS: Process %d set to RUNNING state \n\n", timeString, progId);
                // close file
                fclose(filePtr);
                // stop case
                break;

            // system process selected
            case SYSTEM_PROC_STOP_CODE:
                // print line
                fprintf(filePtr, "\n%s, OS: Process %d ended and set in EXIT state\n",timeString, progId);
                // close file
                fclose(filePtr);
                // stop case
                break;
           }
       }
    if( logToCode != LOGTO_FILE_CODE )
       {
        // switch on message
        switch(commandMsg)
           {
            case SYSTEM_PROC_SELECT_CODE:
                printf("\n%s, OS: Process %d was selected with %d ms, remaining\n", timeString, progId, progRunTime );
                break;
            case SYSTEM_PROC_RUN_CODE:
                printf("%s, OS: Process %d set to RUNNING state \n\n", timeString, progId);
                break;
            case SYSTEM_PROC_STOP_CODE:
                printf("\n%s, OS: Process %d ended and set in EXIT state\n",timeString, progId);
                break;
            
           } 
       }
   }



/*
Function Name: StarterLog()
Algorithm: takes a commandMsg from the sim and a filename
Precondition: requires a valid file string to operate
Postcondition: prints 1 line of the file
Exceptions: This is only to help erase and rstart the file simulation
*/

void StarterLog( int code, int logToCode, char *fileName )
   {
    // initalize file ptr
    FILE *filePtr;
    // if the simulator is booting up 
    if( code == STARTER_CODE )
       {
        // create or erase the log file
        fclose(fopen(fileName, "w"));
       }
    
    // open for append
    filePtr = fopen(fileName, "a+");
      
    // check if failed file
    if( filePtr != NULL && logToCode != LOGTO_MONITOR_CODE)
       {
        // switch on messege code
        switch( code )
           {
            // start simulator
            case STARTER_CODE:
                // print line
                fprintf(filePtr,"Simulator Program\n===================\n");
                // close file
                fclose(filePtr);
                // stop case
                break;

            // Upload Config Data code
            case UPLOAD_CONFIG_CODE:
                // print line
                fprintf(filePtr,"\nUploading Config Data\n");
                // close file
                fclose(filePtr);
                // stop case
                break;

            // upload meta data code
            case UPLOAD_META_CODE:
                // print line
                fprintf(filePtr,"\nUploading Meta Data\n");
                // close file
                fclose(filePtr);
                // stop case
                break;

            // begin simulation run
            case SIM_BEGIN_CODE:
                // print line
                fprintf(filePtr,"\n=========================" 
                                 "\nBEGIN SIMULATOR\n\n");
                // close file
                fclose(filePtr);
                // stop case
                break;

            // end of sim run
            case SIM_END_CODE:
                // print line
                fprintf(filePtr,"\n\nEnd Simulation - Complete" 
                                "\n=========================\n\n");
                // close file
                fclose(filePtr);
                // stop case
                break;
           }
       }
    if( logToCode != LOGTO_FILE_CODE)
       {
        // switch on messege code
        switch( code )
           {
            // start simulator
            case STARTER_CODE:
                // print line
                printf("Simulator Program\n===================\n");
                // stop case
                break;

            // Upload Config Data code
            case UPLOAD_CONFIG_CODE:
                // print line
                printf("\nUploading Config Data\n");
                // stop case
                break;

            // upload meta data code
            case UPLOAD_META_CODE:
                // print line
                printf("\nUploading Meta Data\n");             
                // stop case
                break;

            // begin simulation run
            case SIM_BEGIN_CODE:
                // print line
                printf("\n=========================" 
                                 "\nBEGIN SIMULATOR\n\n");
                // stop case
                break;

            // end of sim run
            case SIM_END_CODE:
                // print line
                printf("\n\nEnd Simulation - Complete" 
                         "\n=========================\n\n");
                // stop case
                break;
           }
       }
   }

/*
Function Name: SystemLogPrint()
Algorithm: takes a commandMsg from the sim and a time string
Precondition: requires a valid file string to operate
Postcondition: prints 1 line of the file
Exceptions: This is to print the Operating System calls
*/

void SystemLogPrint( int commandMsg, int logToCode, char *timeString, char *fileName )
   {
     // initialize file pointer
     FILE *filePtr;
     
     // open file for append
     filePtr = fopen(fileName, "a+");

     // check if open fail
     if( filePtr != NULL && logToCode != LOGTO_MONITOR_CODE)
        {
         // switch on messege
         switch(commandMsg)
            {
             // system start
             case SYSTEM_START_CODE:
                 // print line
                 fprintf(filePtr,"%s, OS: System Start\n",timeString);
                 // close file
                 fclose(filePtr);
                 // stop case
                 break;

             // PCB init
             case SYSTEM_CREATE_PCB_CODE:
                 // print line
                 fprintf(filePtr, "%s, OS: Creating Process Control Blocks\n",timeString);
                 // close file
                 fclose(filePtr);
                 // stop case
                 break;

             // processes set NEW
             case SYSTEM_PROC_INIT_CODE:
                 // print line
                 fprintf(filePtr, "%s, OS: All processes Initialized in NEW state\n",timeString);
                 // close file
                 fclose(filePtr);
                 // stop case
                 break;

             // system Stop
             case SYSTEM_STOP_CODE:
                 // print line
                 fprintf(filePtr, "%s, OS: System Stop\n\n",timeString);
                 // close file
                 fclose(filePtr);
                 // stop case
                 break; 

             // process set in ready
             case SYSTEM_PROC_READY_CODE:
                 // print line
                 fprintf(filePtr, "%s, OS: All processes Set to READY state\n",timeString);
                 // close file
                 fclose(filePtr);
                 // break
                 break;
            }
        }
     else
        {
         // display error
         printf("\nFile Open Failed\n");
        }

     if( logToCode != LOGTO_FILE_CODE )
        {
         switch(commandMsg)
            {
             case SYSTEM_START_CODE:
                 printf("%s, OS: System Start\n",timeString);
                 break;
             case SYSTEM_CREATE_PCB_CODE:
                 printf("%s, OS: Creating Process Control Blocks\n",timeString);
                 break;
             case SYSTEM_PROC_INIT_CODE:
                 printf("%s, OS: All processes Initialized in NEW state\n",timeString);
                 break;
             case SYSTEM_STOP_CODE:
                 printf("%s, OS: System Stop\n\n",timeString);
                 break; 
             case SYSTEM_PROC_READY_CODE:
                 printf("%s, OS: All Processes Set to READY state\n",timeString);
                 break;
            }
       }    
        }




void displayInternalString( int commandMsg, char *timeString , int progId, char *nameString, char *startEndString )
   {

  }


int getCommand( char commandMsg)
   {
    switch(commandMsg)
       {
        case 'O':
            return PROCESS_OUTPUT_CODE;
        case 'I':
            return PROCESS_INPUT_CODE;
        case 'M':
            return PROCESS_MEMORY_CODE;
        default:
            return PROCESS_RUN_CODE; 
       }
   }


void getOpLetterString( OpCodeType opCode, char **resultString )
   {
    switch(opCode.opLtr)
       {
        case 'S': // check for system command
           copyString(*resultString,"System");
           break;
        case 'A':
           copyString(*resultString,"Application");
           break;
        case 'I':
           copyString(*resultString,"input");
           break;
        case 'O':
           copyString(*resultString,"output");
           break;
        case 'M':
           copyString(*resultString,"MMU");
           break;
        case 'P':
           copyString(*resultString,"printer");
           break;
        default:
           copyString(*resultString,"operation");
           break;
       }
   }


#endif
