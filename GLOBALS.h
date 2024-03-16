#ifndef GLOBALS_H
#define GLOBALS_H

#include "INCLUDES.h"

uint32_t CURRENT_CYCLE = 0;             // The current cycle that each process is on
uint32_t TOTAL_CREATED_PROCESSES = 0;   // The total number of processes constructed
uint32_t TOTAL_STARTED_PROCESSES = 0;   // The total number of processes that have started being simulated
uint32_t TOTAL_FINISHED_PROCESSES = 0;  // The total number of processes that have finished running
uint32_t TOTAL_NUMBER_OF_CYCLES_SPENT_BLOCKED = 0; // The total cycles in the blocked state
uint32_t QUANTUM_LENGTH = 2;

#define BLACK "\033[0;30m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"
#define RESET "\033[0m"

typedef enum {false, true} bool;        // Allows boolean types in C

//***************************************************************************************************************************************************************//
//     function call        : pause_terminal()
//     function description : this function will pause the terminal until the user presses the enter key
//     function inputs      : void
//     function outputs     : void
//     preconditions        : none
//     postconditions       : none
//     created              ; 2/7/2024
//     last edited          : 2/7/2024
//     programmer           : Sam Stanley

void pause_terminal(void)
{
    char c;
    printf("    press "MAGENTA"ENTER"RESET" to continue...");
    c = getchar();
    printf("\n\n");
}

//***************************************************************************************************************************************************************//
//     function call        : clear_terminal()
//     function description : this function will clear the terminal of all text
//     function inputs      : void
//     function outputs     : void
//     preconditions        : CLEAR is defined correctly
//     postconditions       : none
//     created              ; 2/7/2024
//     last edited          : 2/7/2024
//     programmer           : Sam Stanley

void clear_terminal(void)
{
	system(CLEAR);
}

//***************************************************************************************************************************************************************//

#endif