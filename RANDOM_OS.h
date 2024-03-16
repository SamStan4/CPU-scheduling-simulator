#ifndef RANDOM_OS_H
#define RANDOM_OS_H

#include "GLOBALS.h"

const char* RANDOM_NUMBER_FILE_NAME= "random-numbers";
const uint32_t SEED_VALUE = 200;  // Seed value for reading from file



uint32_t getRandNumFromFile(uint32_t line, FILE* random_num_file_ptr){
    uint32_t end, loop;
    char str[512];

    rewind(random_num_file_ptr); // reset to be beginning
    for(end = loop = 0;loop<line;++loop){
        if(0==fgets(str, sizeof(str), random_num_file_ptr)){ //include '\n'
            end = 1;  //can't input (EOF)
            break;
        }
    }
    if(!end) {
        return (uint32_t) atoi(str);
    }

    // fail-safe return
    return (uint32_t) 1804289383;
}



/**
 * Reads a random non-negative integer X from a file named random-numbers.
 * Returns the CPU Burst: : 1 + (random-number-from-file % upper_bound)
 */
uint32_t randomOS(uint32_t upper_bound, uint32_t process_indx, FILE* random_num_file_ptr)
{
    char str[20];
    
    uint32_t unsigned_rand_int = (uint32_t) getRandNumFromFile(SEED_VALUE+process_indx, random_num_file_ptr);
    uint32_t returnValue = 1 + (unsigned_rand_int % upper_bound);

    return returnValue;
} 

//***************************************************************************************************************************************************************//
//     function call        : random_os_wrapper()
//     function description : this function will take the upper bound and index of a process and return a pseudo random number using those inputs
//     function inputs      : uint32_t X2
//     function outputs     : uint32_t
//     preconditions        : random number file exists
//     postconditions       : none
//     created              ; 3/3/2024
//     last edited          : 3/3/2024
//     programmer           : Sam Stanley


uint32_t random_os_wrapper(uint32_t upper_bound, uint32_t process_indx)
{
    FILE* ran_file = fopen(RANDOM_NUMBER_FILE_NAME, "r");
    uint32_t result = 0;

    if (ran_file != NULL)
    {
        result = randomOS(upper_bound, process_indx, ran_file);

        fclose(ran_file);

        return result;
    }
    else
    {
        printf(RED"RAN FILE WAS NULL\n"RESET);

        return 0;
    }
}

//***************************************************************************************************************************************************************//

#endif