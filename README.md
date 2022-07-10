# Sofware Simulated Operating System
This application is a new and improved implimentation of the OS project that was assigned to our class in my college undergrad program. The idea is
that we are creating a software based 'Operating System' that is capable of multithreading and moving through system 'processes' by reading a
data file in the form of UTF-8 strings and performing the various 'operations' with the software based 'processor'. I am redoing this project
to re-learn some pointer and memory logical processes and practices in C again.

The main focus of this project is to mimic all important parts to an operating system inluding the memory management system, CPU scheduling
algorithms and 'system configurations' and even an event logging system.

Design:
---
Boot Process:
	1. Read the configuration file in and set system information in the processor/memory
Processor:
	1. Read the process files for each 'process' that needs to be run
Timer:
	1. "Internal Clock System" that controls how long each 'cycle' takes in the processor. 
		- 2 modes; syncronous(with holding loops) and asyncronous (w/ interrupts) ?
	2. Sends interrupts after doing stated number of cycles for the processor
Memory:
	1. Needs a PCB struct to mimic a data entry in the process control blocks.
	2. Active PCBs and used to hold running processes in the processor and hold active data from the processes that are still running but not activly working in the CPU
Logger:
	1. logs the process of the CPU,Memory,Config, etxc into an ourput file or to the users console for easier debugging of the program flow


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
**Note: This is mimicing the concept of a processor executing any action that appears in the list of processor actions in the form
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