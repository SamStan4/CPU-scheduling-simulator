#ifndef SCHEDULER_WRAPPER
#define SCHEDULER_WRAPPER

#include "PRINT_HELPERS.h"
#include "error_handler.h"

#include "FCFS.h"
#include "RR.h"
#include "SJF.h"


//***************************************************************************************************************************************************************//
//     function call        : get_file_name()
//     function description : this function will load all of the processes from the file
//     function inputs      : _process*, uint32_t*, char*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/2/2024
//     last edited          : 3/2/2024
//     programmer           : Sam Stanley

char* get_file_name(int argument_count, char* argument_vector[])
{
    FILE* find_file = NULL;

    // TEST
    //printf("validating file\n");
    // END TEST

    if (argument_count <= 1) // no file given
    {
        error_thrower(NO_FILE_GIVEN_ERROR, "");
        pause_terminal();
        return NULL;
    }
    else if (argument_count > 2)
    {
        error_thrower(TOO_MANY_FILES_GIVEN_ERROR, "");
        pause_terminal();
        return NULL;
    }
    else // there is only one file, so check if it exists
    {
        find_file = fopen(argument_vector[1], "r"); // attempt to open the file in read mode

        if (find_file == NULL) // couldnt find the file
        {
            error_thrower(FILE_DOESNT_EXIST_ERROR, argument_vector[1]);
            pause_terminal();
            return NULL;
        }
        else
        {
            fclose(find_file);
            return argument_vector[1];
        }
    }
}

//***************************************************************************************************************************************************************//
//     function call        : FCFS_routine_wrapper()
//     function description : this function will wrap the FCFS scheduler logic
//     function inputs      : _process*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 2/28/2024
//     last edited          : 2/28/2024
//     programmer           : Sam Stanley

void FCFS_routine_wrapper(_process* process_list)
{
    _process* FCFS_list = copy_process_list(process_list, TOTAL_CREATED_PROCESSES);
    p_trace FCFS_trace;
    trace_constructor(&FCFS_trace);

    CURRENT_CYCLE = 0;                          // reset all of these globals
    TOTAL_STARTED_PROCESSES = 0;
    TOTAL_FINISHED_PROCESSES = 0;
    TOTAL_NUMBER_OF_CYCLES_SPENT_BLOCKED = 0;

    run_FCFS_routine(FCFS_list, &FCFS_trace); // actually running the thing

    printf(GREEN"######################### "MAGENTA"START OF FIRST COME FIRST SERVE"GREEN" #########################\n"RESET);
    printStart(process_list);
    printFinal(FCFS_list);
    printf("\n");
    print_process_trace(&FCFS_trace, TOTAL_CREATED_PROCESSES);
    printf("\nThe scheduling algorithm used was First Come First Serve\n\n");
    printProcessSpecifics(FCFS_list);
    printSummaryData(FCFS_list);
    printf(GREEN"######################### "MAGENTA"END OF FIRST COME FIRST SERVE"GREEN" #########################\n"RESET);

    process_list_destructor(FCFS_list);
    trace_destructor(&FCFS_trace);

}

//***************************************************************************************************************************************************************//
//     function call        : RR_routine_wrapper()
//     function description : this function will wrap the RR scheduler logic
//     function inputs      : _process*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 2/28/2024
//     last edited          : 2/28/2024
//     programmer           : Sam Stanley

void RR_routine_wrapper(_process* process_list)
{
    _process* RR_list = copy_process_list(process_list, TOTAL_CREATED_PROCESSES);
    p_trace RR_trace;
    trace_constructor(&RR_trace);

    CURRENT_CYCLE = 0;                          // reset all of these globals
    TOTAL_STARTED_PROCESSES = 0;
    TOTAL_FINISHED_PROCESSES = 0;
    TOTAL_NUMBER_OF_CYCLES_SPENT_BLOCKED = 0;

    run_RR_routine(RR_list, &RR_trace);


    printf(GREEN"######################### "MAGENTA"START OF ROUND ROBIN"GREEN" #########################\n"RESET);
    printStart(process_list);
    printFinal(RR_list);
    printf("\n");
    print_process_trace(&RR_trace, TOTAL_CREATED_PROCESSES);
    printf("\nThe scheduling algorithm used was Round Robin\n");
    printProcessSpecifics(RR_list);
    printSummaryData(RR_list);
    printf(GREEN"######################### "MAGENTA"END OF ROUND ROBIN"GREEN" #########################\n"RESET);

    process_list_destructor(RR_list);
    trace_destructor(&RR_trace);

}

//***************************************************************************************************************************************************************//
//     function call        : SJF_routine_wrapper()
//     function description : this function will wrap the SJF scheduler logic
//     function inputs      : _process*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 2/28/2024
//     last edited          : 2/28/2024
//     programmer           : Sam Stanley

void SJF_routine_wrapper(_process* process_list)
{
    _process* SJF_list = copy_process_list(process_list, TOTAL_CREATED_PROCESSES);
    p_trace SJF_trace;
    trace_constructor(&SJF_trace);

    CURRENT_CYCLE = 0;                          // reset all of these globals
    TOTAL_STARTED_PROCESSES = 0;
    TOTAL_FINISHED_PROCESSES = 0;
    TOTAL_NUMBER_OF_CYCLES_SPENT_BLOCKED = 0;

    run_SJF_routine(SJF_list, &SJF_trace);

    printf(GREEN"######################### "MAGENTA"START OF SHORTEST JOB FIRST"GREEN" #########################\n"RESET);
    printStart(process_list);
    printFinal(SJF_list);
    printf("\n");
    print_process_trace(&SJF_trace, TOTAL_CREATED_PROCESSES);
    printf("\nThe scheduling algorithm used was Shortest Job First\n");
    printProcessSpecifics(SJF_list);
    printSummaryData(SJF_list);
    printf(GREEN"######################### "MAGENTA"END OF SHORTEST JOB FIRST"GREEN" #########################\n"RESET);

    process_list_destructor(SJF_list);
    trace_destructor(&SJF_trace);
}


//***************************************************************************************************************************************************************//
//     function call        : run_schedulers()
//     function description : this function will run each the FCFS, RR, and SJF schedulers
//     function inputs      : _process, uint32_t
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 2/28/2024
//     last edited          : 2/28/2024
//     programmer           : Sam Stanley

void run_schedulers(_process* process_list)
{
    FCFS_routine_wrapper(process_list);
    RR_routine_wrapper(process_list);
    SJF_routine_wrapper(process_list);
}

//***************************************************************************************************************************************************************//
//     function call        : scheduler_wrapper()
//     function description : this function will serve as a wrapper for the program
//     function inputs      : _process, uint32_t
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 2/28/2024
//     last edited          : 2/28/2024
//     programmer           : Sam Stanley

void scheduler_wrapper(int argument_count, char* argument_vector[])
{
    uint32_t total_num_of_process;               // Read from the file -- number of process to create
    _process* process_list = NULL; // Creates a container for all processes
    char* file_name = NULL;

    clear_terminal(); // do this to get rid of all of the other stuff that might be there

    file_name = get_file_name(argument_count, argument_vector);

    if (file_name != NULL)
    {
        process_list = load_process_list(&total_num_of_process, file_name);

        populate_process_ID(process_list, total_num_of_process);

        run_schedulers(process_list);
    }

    process_list_destructor(process_list);
    
}

//***************************************************************************************************************************************************************//
#endif