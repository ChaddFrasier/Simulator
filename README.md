# Software Simulated Operating System
This application is a new and improved implementation of the OS project that was assigned to our class in my college undergrad program. The idea is
that we are creating a software based 'Operating System' that is capable of multithreading and moving through system 'processes' by reading a
data file in the form of UTF-8 strings and performing the various 'operations' with the software based 'processor'. I am redoing this project
to re-learn some pointer and memory logical processes and practices in C again.

The main focus of this project is to mimic all important parts to an operating system including the memory management system, CPU scheduling
algorithms and 'system configurations' and even an event logging system.

Design:
---
Boot Process:
	1. Read the configuration file in and set system information in the processor/memory
Processor:
	1. Read the process files for each 'process' that needs to be run
	2. Multiple scheduling algorithms
		- First Come First Serve(FCFS)
		- Shortest Job First(SJF)
		- Round Robin
Timer:
	1. "Internal Clock System" that controls how long each 'cycle' takes in the processor. 
		- 2 modes; synchronous(with holding loops) and asynchronous (w/ interrupts) ?
	2. Sends interrupts after doing stated number of cycles for the processor
Memory:
	1. Needs a PCB struct to mimic a data entry in the process control blocks.
	2. Active PCBs and used to hold running processes in the processor and hold active data from the processes that are still running but not actively working in the CPU
Logger:
	1. logs the process of the CPU,Memory,Config, etc into an output file or to the users console for easier debugging of the program flow


Goal:
---
Write a program that can read in a configuration file of the form
```
SYSTEM_CONFIG
Version: 1.05
Process Path: metadata3a.mdf
Scheduling Algorithm: SJF-N
Quantum Time (cycles): 3 
Processor Cycle Time (msec): 10
Memory Available (MB): 995
I/O Cycle Time (msec): 20
Log To: Both
Log File Path: logfile_1.lgf
SYSTEM_CONFIG_END
```

And then uses the listed metadata file to read in the process of the form to create a PCB list for each process in the metadata file. 
**Note: This is mimicking the concept of a processor executing any action that appears in the list of processor actions in the form
of a file, the creating a process control structure to then execute that process over X amount of cycles of the processor.**
```
Start Program Meta-Data Code:
S(start)0; A(start)0; I(keyboard)130; P(run)8;
P(run)14; O(printer)12; P(run)8; I(keyboard)170; P(run)30;
O(printer)35; O(hard drive)39; A(end)0; A(start)0; I(keyboard)110; M(allocate)14200100; P(run)8;
P(run)14; O(printer)65; P(run)8; M(access)14210010 I(keyboard)110; P(run)11;
O(printer)35; O(hard drive)39; A(end)0; A(start)0; I(keyboard)130; P(run)8;
P(run)14; O(printer)12; P(run)8; I(keyboard)90; P(run)11;
O(printer)35; M(allocate)14200100; M(allocate)20301050; O(hard drive)53; A(end)0;  S(end)0;
End Program Meta-Data Code.
```

## Environment Setup
1. GNU Compiler (GCC v6.3.0)
2. VS Code (IDE)
3. CMake 
4. Make (Chocolatey for Windows)
5. Git
6. VSCode Extensions:
	- CMake Language Support
	- CMake Tools
	- C/C++ Tools
	- C/C++ Extensions Pack
	- C++ Better Syntax

## Scripts
### Build Project Script
*Bash Script*: `./buildProject`

### Run Script
*Bash Script*: `./run`

### Build and Unit Test Script
*Bash Script*: `./build_and_test`

### Unit Test Script
*Bash Script*: `./test`

## Writing Unit Tests
There are only 2 main steps to writing a unit test for this project.
1. Create the test file
2. Add the test executable to the ctest cmake file
====
1. Create a new directory for the test in ctest/src and create a new test file for each unit you want to test independantly.
*NEW_TEST.c*
```{c}
#ifndef TEST_C
#define TEST_C

#include "../../headers/tests.h"
#include "../../../src/<UNIT TO TEST>/<UNIT TO TEST>.h"
TEST{
	// success? return PASS;
    if( true ) {
        return PASS;
    } else { // if test failed? return FAIL;
        return FAIL;
    }

	// SHOULD ALWAYS FAIL BY DEFAULT. ONLY SUCCEED WHEN YOU FORCE THE SUCCESS
    return FAIL;
}
#endif
```

2. Add the test executables into the project. Simply add these three lines into the cmake file at the ctest level.
_Note: Please follow the format that is layed out already in the file_
*ctest\CMakeLists.txt*
```{cmake}
add_executable(NewTest src/NewTest/newtest.test.c)

target_link_libraries(NewTest PRIVATE UNIT_TO_TEST)

add_test(NAME NewTest COMMAND NewTest)
```