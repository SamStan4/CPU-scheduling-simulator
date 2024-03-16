#ifndef TRACE_H
#define TRACE_H
 
#define UNSTARTED_ptrace  "   unstarted  "
#define READY_ptrace      "     ready    "
#define RUNNING_ptrace    "    running   "
#define BLOCKED_ptrace    "    blocked   "
#define TERMINATED_ptrace "  terminated  "

#include "process_list.h"

typedef struct p_trace
{
    int num_traces;
    _process** trace_list;
} p_trace;

//***************************************************************************************************************************************************************//
//     function call        : trace_constructor()
//     function description : this function will initialize the p_trace struct
//     function inputs      : p_trace*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/7/2024
//     last edited          : 3/7/2024
//     programmer           : Sam Stanley

void trace_constructor(p_trace* trace)
{
    trace->num_traces = 0;
    trace->trace_list = NULL;
}

//***************************************************************************************************************************************************************//
//     function call        : trace_destructor()
//     function description : this function will deallocate all memory in the p_trace struct
//     function inputs      : p_trace*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/7/2024
//     last edited          : 3/7/2024
//     programmer           : Sam Stanley

void trace_destructor(p_trace* trace)
{
    // very complicated

    int i = 0;

    for (i = 0; i < trace->num_traces; ++i)
    {
        free(trace->trace_list[i]); // delete the initiali traces
        trace->trace_list[i] = NULL;
    }

    free(trace->trace_list); // now free the list its self
    trace->trace_list = NULL;
}

//***************************************************************************************************************************************************************//
//     function call        : push_trace()
//     function description : this function will push a snapshot of the current process list to the trace
//     function inputs      : p_trace*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/7/2024
//     last edited          : 3/7/2024
//     programmer           : Sam Stanley

void push_trace(p_trace* trace, _process* process_list, uint32_t process_list_size)
{
    trace->trace_list = (_process**) realloc(trace->trace_list, ((trace->num_traces + 1) * sizeof(_process*)));
    trace->trace_list[trace->num_traces] = copy_process_list(process_list, process_list_size);
    trace->num_traces += 1;
}

//***************************************************************************************************************************************************************//
//     function call        : push_trace()
//     function description : this function will print out the entire trace to the terminal screen
//     function inputs      : p_trace*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/7/2024
//     last edited          : 3/7/2024
//     programmer           : Sam Stanley

void print_process_trace(p_trace* trace, uint32_t num_processes)
{
    int i = 0, j = 0, k = 0;


    printf("This detailed printout gives the state for each process\n");

    printf(BLUE"|------------------|"RESET);

    for (k = 0; k < num_processes; ++k)
    {
        printf(BLUE"--------------|"RESET);
    } 

    printf("\n");

    printf(BLUE"|"RESET"     Process:     "BLUE"|"RESET);

    for (k = 0; k < num_processes; ++k)
    {
        if (k < 10)
        {
            printf(" ");
        }

        printf("  process %d ", k);

        if (k < 100)
        {
            printf(" ");
        }

        printf(BLUE"|"RESET);
    }

    printf("\n");

    printf(BLUE"|------------------|"RESET);

    for (k = 0; k < num_processes; ++k)
    {
        printf(BLUE"--------------|"RESET);
    } 


    printf("\n");

    for (i = 0; i < trace->num_traces; ++i)
    {
        printf(BLUE"|"RESET" Before cycle ");
    
        if (i < 10)
        {
            printf(" ");
        }
        if (i < 100)
        {
            printf(" ");
        }

        printf("%d "BLUE"|"RESET, i);

        for (j = 0; j < num_processes; ++j)
        {
            if (trace->trace_list[i][j].status == IS_UNSTARTED)
            {
                printf(RED);
                printf(UNSTARTED_ptrace);
                printf(RESET);
            }
            else if (trace->trace_list[i][j].status == IS_READY)
            {
                printf(YELLOW);
                printf(READY_ptrace);
                printf(RESET);
            }
            else if (trace->trace_list[i][j].status == IS_RUNNING)
            {
                printf(GREEN);
                printf(RUNNING_ptrace);
                printf(RESET);
            }
            else if (trace->trace_list[i][j].status == IS_BLOCKED)
            {
                printf(MAGENTA);
                printf(BLOCKED_ptrace);
                printf(RESET);
            }
            else if (trace->trace_list[i][j].status == IS_TERMINATED)
            {
                printf(CYAN);
                printf(TERMINATED_ptrace);
                printf(RESET);
            }

            printf(BLUE"|"RESET);

        }

        printf("\n");
    }

    printf(BLUE"|------------------|"RESET);

    for (k = 0; k < num_processes; ++k)
    {
        printf(BLUE"--------------|"RESET);
    } 

    printf("\n");
    
}


//***************************************************************************************************************************************************************//

#endif