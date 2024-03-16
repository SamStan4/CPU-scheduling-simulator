#ifndef PROCESS_LIST_H
#define PROCESS_LIST_H

#include "process.h"
#include "string_methods.h"

#define UNSTARTED_s " unstarted"
#define READY_S "     ready"
#define RUNNING_s "   running"
#define BLOCKED_s "   blocked"
#define TERMINATED_s "terminated"
 
//***************************************************************************************************************************************************************//
//     function call        : load_process_list()
//     function description : this function will load all of the processes from the file
//     function inputs      : _process*, uint32_t*, char*
//     function outputs     : none
//     preconditions        : the file that is passed in is well formed, global variables are all defined
//     postconditions       : none
//     created              ; 3/2/2024
//     last edited          : 3/2/2024
//     programmer           : Sam Stanley

typedef enum {
    waiting = 0,          // not inside a process
    A_FIELD = 1,          // reading characters for the A field
    B_FIELD = 2,          // reading characters for the B field
    C_FIELD = 3,          // reading characters for the C field
    M_FIELD = 4,          // reading characters for the M field
    A_FIELD_waiting = 5,  // waiting to read characters for the A field
    B_FIELD_waiting = 6,  // waiting to read characters for the B field
    C_FIELD_waiting = 7,  // waiting to read characters for the C field
    M_FIELD_waiting = 8   // waiting to read characters for the M field
} field;

_process* load_process_list(uint32_t* num_processes, char* file_name)
{
    // test
    //printf("Here is the input file --> %s\n", file_name);
    // end test

    FILE* input_stream = fopen(file_name, "r");
    char
        read_string[5000] = {'\0'},
        s_num_processes[10] = {'\0'},
        s_temp_num[10] = {'\0'};
    int i = 0, j = 0;
    _process* new_list = NULL;
    bool inside_par = false;
    field current_field = waiting;

    if (input_stream == NULL) // failure to open file
    {
        return NULL;
    }

    fgets(read_string, 5000, input_stream); // only read the one line

    fclose(input_stream);

    // get the number of processes here --> 
    for (i = 0; read_string[i] != ' '; ++i)
    {
        s_num_processes[i] = read_string[i];
    }
    // now we have the number that we want

    //TEST
    //printf("Here is the nuber of processes --> %s\n", s_num_processes);
    //END TEST

    *num_processes = atoi(s_num_processes);     // set these two to the number of processes that we are going to create
    TOTAL_CREATED_PROCESSES = *num_processes;
    
    // allocate space for our process list -->
    new_list = (_process*) calloc (sizeof(_process), *num_processes);

    // TEST
    //printf("made it here\n");
    // END TEST

    // initialize the process list -->

    for (j = 0; j < TOTAL_CREATED_PROCESSES; ++j)
    {
        process_constructor(&new_list[j]);
    }

    // TEST
    //printf("process list initialized\n");
    // END TEST

    // populate the process listv -->

    for (j = 0; (i < 5000) && (j < *num_processes) && (read_string[i] != '\0'); ++i)
    {
        if (read_string[i] == '(') // going into a process
        {
            inside_par = true;
            current_field = A_FIELD_waiting;
            // test ///////////
            //printf("'(' HIT\n");
            // end test ///////

        }
        else if (read_string[i] == ')') // exiting a process
        {
            inside_par = false;
            current_field = waiting;
            new_list[j].M = atoi(s_temp_num);
            initialize_string(s_temp_num, '\0', 10);
            ++j;
            // test ///////////
            //printf("')' HIT\n");
            // end test ///////
        }
        else
        {
            if (inside_par == true) // we are inside a current process
            {
                if (current_field == A_FIELD_waiting)
                {
                    if (read_string[i] != ' ') // we should be looking at a number
                    {
                        current_field = A_FIELD;
                        char_concatinate(s_temp_num, read_string[i], 10);
                        // test ///////////
                        //printf("' ' HIT INSIDE A_FIELD_waiting\n");
                        // end test ///////

                    }
                }
                else if (current_field == B_FIELD_waiting)
                {
                    if (read_string[i] != ' ') // we should be looking at a number
                    {
                        current_field = B_FIELD;
                        char_concatinate(s_temp_num, read_string[i], 10);
                        // test ///////////
                        //printf("' ' HIT INSIDE B_FIELD_waiting\n");
                        // end test ///////
                    }
                }
                else if (current_field == C_FIELD_waiting)
                {
                    if (read_string[i] != ' ') // we should be looking at a number
                    {
                        current_field = C_FIELD;
                        char_concatinate(s_temp_num, read_string[i], 10);
                        // test ///////////
                        //printf("' ' HIT INSIDE C_FIELD_waiting\n");
                        // end test ///////
                    }
                }
                else if (current_field == M_FIELD_waiting)
                {
                    if (read_string[i] != ' ') // we should be looking at a number
                    {
                        current_field = M_FIELD;
                        char_concatinate(s_temp_num, read_string[i], 10);
                        // test ///////////
                        //printf("' ' HIT INSIDE M_FIELD_waiting\n");
                        // end test ///////
                    }
                }
                else if (current_field == A_FIELD)
                {
                    if (read_string[i] != ' ') // cat another number
                    {
                        char_concatinate(s_temp_num, read_string[i], 10);
                        // test ///////////
                        //printf("'N' HIT INSIDE A_FIELD\n");
                        // end test ///////
                    }
                    else // done reading this field
                    {
                        new_list[j].A = atoi(s_temp_num);
                        current_field = B_FIELD_waiting;
                        initialize_string(s_temp_num, '\0', 10);
                        // test ///////////
                        //printf("' ' HIT INSIDE A_FIELD\n");
                        // end test ///////
                    }
                }
                else if (current_field == B_FIELD)
                {
                    if (read_string[i] != ' ') // cat another number
                    {
                        char_concatinate(s_temp_num, read_string[i], 10);
                        // test ///////////
                        //printf("'N' HIT INSIDE B_FIELD\n");
                        // end test ///////
                    }
                    else // done reading this field
                    {
                        new_list[j].B = atoi(s_temp_num);
                        current_field = C_FIELD_waiting;
                        initialize_string(s_temp_num, '\0', 10);
                        // test ///////////
                        //printf("' ' HIT INSIDE B_FIELD\n");
                        // end test ///////
                    }
                }
                else if (current_field == C_FIELD)
                {
                    if (read_string[i] != ' ') // cat another number
                    {
                        char_concatinate(s_temp_num, read_string[i], 10);
                        // test ///////////
                        //printf("'N' HIT INSIDE C_FIELD\n");
                        // end test ///////
                    }
                    else // done reading this field
                    {
                        new_list[j].C = atoi(s_temp_num);
                        current_field = M_FIELD_waiting;
                        initialize_string(s_temp_num, '\0', 10);
                        // test ///////////
                        //printf("' ' HIT INSIDE C_FIELD\n");
                        // end test ///////
                    }
                }
                else if (current_field == M_FIELD)
                {
                    if (read_string[i] != ' ') // cat another number
                    {
                        char_concatinate(s_temp_num, read_string[i], 10);
                        // test ///////////
                        //printf("'N' HIT INSIDE M_FIELD\n");
                        // end test ///////
                    }
                    else // done reading this field
                    {
                        new_list[j].M = atoi(s_temp_num);
                        current_field = waiting;
                        initialize_string(s_temp_num, '\0', 10);
                        // test ///////////
                        //printf("' ' HIT INSIDE M_FIELD\n");
                        // end test ///////
                    }
                }
            }
        }
    }

    return new_list;

}

//***************************************************************************************************************************************************************//
//     function call        : print_process_list()
//     function description : this function will printf out the list of processes, it is to be used for testing/debugging
//     function inputs      : _process*, uint32_t
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/2/2024
//     last edited          : 3/2/2024

void print_process_list(_process* process_list, uint32_t num_processes)
{
    int i = 0;
    printf("%d ", num_processes);
    for (i = 0; i < num_processes; ++i)
    {
        printf("(%d %d %d %d) ", process_list[i].A, process_list[i].B, process_list[i].C, process_list[i].M);
    }
    printf("\n");
}

//***************************************************************************************************************************************************************//
//     function call        : print_process_list_enhanced()
//     function description : this function will printf out the list of processes and more of the attributes, it is to be used for testing/debugging
//     function inputs      : _process*, uint32_t
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/2/2024
//     last edited          : 3/2/2024

void print_process_list_enhanced(_process* process_list, uint32_t num_processes)
{
    int i = 0;
    for (i = 0; i < num_processes; ++i)
    {
        print_process(&process_list[i]);
        printf("\n");
    }
}

//***************************************************************************************************************************************************************//
//     function call        : populate_process_ID()
//     function description : this function will populate the process ID part of the process
//     function inputs      : _process*, uint32_t
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/2/2024
//     last edited          : 3/2/2024
//     programmer           : Sam Stanley

void populate_process_ID(_process* p_list, uint32_t num_processes)
{
    int i = 0;
    for (i = 0; i < num_processes; ++i)
    {
        p_list[i].processID = i;
    }
}

//***************************************************************************************************************************************************************//
//     function call        : sort_list_arrival_time()
//     function description : this function will sort the list based off the arrival time using bubble sort
//     function inputs      : none
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/2/2024
//     last edited          : 3/2/2024
//     programmer           : Sam Stanley

void swap_processes(_process* process_one, _process* process_two)
{
    _process temp;
    memcpy(&temp, process_one, sizeof(_process));
    memcpy(process_one, process_two, sizeof(_process));
    memcpy(process_two, &temp, sizeof(_process));

}

//***************************************************************************************************************************************************************//
//     function call        : sort_list_arrival_time()
//     function description : this function will sort the list based off the arrival time using bubble sort
//     function inputs      : none
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/2/2024
//     last edited          : 3/2/2024
//     programmer           : Sam Stanley

void sort_list_arrival_time(_process* process_list)
{
    int i = 0, j = 0, passes = 0;

    for (i = 0; i < TOTAL_CREATED_PROCESSES; ++i)
    {
        for (j = 0; j < (TOTAL_CREATED_PROCESSES - i - 1); ++j)
        {
            if (process_list[j].A > process_list[j + 1].A) // swap
            {
                swap_processes(&process_list[j], &process_list[j + 1]);
            }
            else if (process_list[j].A == process_list[j + 1].A)
            {
                if (process_list[j].processID > process_list[j + 1].processID) // swap
                {
                    swap_processes(&process_list[j], &process_list[j + 1]);
                }
            }
        }
    }
}

//***************************************************************************************************************************************************************//
//     function call        : sort_list_CPU_time()
//     function description : this function will sort the list based off the CPU time using bubble sort
//     function inputs      : none
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/2/2024
//     last edited          : 3/2/2024
//     programmer           : Sam Stanley

void sort_list_CPU_time(_process* process_list)
{
    int i = 0, j = 0, passes = 0;

    for (i = 0; i < TOTAL_CREATED_PROCESSES; ++i)
    {
        for (j = 0; j < (TOTAL_CREATED_PROCESSES - i - 1); ++j)
        {
            if (process_list[j].C > process_list[j + 1].C) // swap
            {
                swap_processes(&process_list[j], &process_list[j + 1]);
            }
            else if (process_list[j].C == process_list[j + 1].C)
            {
                if (process_list[j].processID > process_list[j + 1].processID) // swap
                {
                    swap_processes(&process_list[j], &process_list[j + 1]);
                }
            }
        }
    }
}

//***************************************************************************************************************************************************************//
//     function call        : sort_list_finish_time()
//     function description : this function will sort the list based off the finishing time using bubble sort
//     function inputs      : none
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/2/2024
//     last edited          : 3/2/2024
//     programmer           : Sam Stanley

void sort_list_finish_time(_process* process_list)
{
    int i = 0, j = 0, passes = 0;

    for (i = 0; i < TOTAL_CREATED_PROCESSES; ++i)
    {
        for (j = 0; j < (TOTAL_CREATED_PROCESSES - i - 1); ++j)
        {
            if (process_list[j].finishingTime > process_list[j + 1].finishingTime) // swap
            {
                swap_processes(&process_list[j], &process_list[j + 1]);
            }
            else if (process_list[j].finishingTime == process_list[j + 1].finishingTime)
            {
                if (process_list[j].processID > process_list[j + 1].processID) // swap
                {
                    swap_processes(&process_list[j], &process_list[j + 1]);
                }
            }
        }
    }
}

//***************************************************************************************************************************************************************//
//     function call        : sort_list_ID()
//     function description : this function will sort the list based off the process ID using bubble sort
//     function inputs      : _process*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/2/2024
//     last edited          : 3/2/2024
//     programmer           : Sam Stanley

void sort_list_ID(_process* process_list)
{
    int i = 0, j = 0, passes = 0;

    for (i = 0; i < TOTAL_CREATED_PROCESSES; ++i)
    {
        for (j = 0; j < (TOTAL_CREATED_PROCESSES - i - 1); ++j)
        {
            if (process_list[j].processID > process_list[j + 1].processID) // swap
            {
                swap_processes(&process_list[j], &process_list[j + 1]);
            }
        }
    }
}


//***************************************************************************************************************************************************************//
//     function call        : copy_process_list()
//     function description : this function will creat a dynamic copy of the process list
//     function inputs      : _process*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/2/2024
//     last edited          : 3/2/2024
//     programmer           : Sam Stanley

_process* copy_process_list(_process* p_list, uint32_t size)
{
    _process* new_list = (_process*) calloc (size, sizeof(_process));
    int i = 0;

    if (new_list != NULL)
    {
        for (i = 0; i < size; ++i)
        {
            memcpy(&new_list[i], &p_list[i], sizeof(_process));
        }
    }

    return new_list;
}

//***************************************************************************************************************************************************************//
//     function call        : process_list_destructor()
//     function description : this function will deallocate the process list
//     function inputs      : _process*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/2/2024
//     last edited          : 3/2/2024
//     programmer           : Sam Stanley

void process_list_destructor(_process* p_list)
{
    free(p_list);
}

//***************************************************************************************************************************************************************//
//     function call        : print_process_list_trace()
//     function description : this function will deallocate the process list
//     function inputs      : _process*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/2/2024
//     last edited          : 3/2/2024
//     programmer           : Sam Stanley


void print_process_list_trace(_process* process_list, uint32_t num_processes, uint32_t current_cycle)
{
    int i = 0;

    printf("[%d] Before cycle ", num_processes);
    
    if (current_cycle < 10)
    {
        printf(" ");
    }
    if (current_cycle < 100)
    {
        printf(" ");
    }

    printf("%d:     ", current_cycle);

    for (i = 0; i < num_processes; ++i)
    {
        if (process_list[i].status == IS_UNSTARTED)
        {
            printf(RED);
            printf(UNSTARTED_s);
            printf(RESET);
        }
        else if (process_list[i].status == IS_READY)
        {
            printf(YELLOW);
            printf(READY_S);
            printf(RESET);
        }
        else if (process_list[i].status == IS_RUNNING)
        {
            printf(GREEN);
            printf(RUNNING_s);
            printf(RESET);
        }
        else if (process_list[i].status == IS_BLOCKED)
        {
            printf(MAGENTA);
            printf(BLOCKED_s);
            printf(RESET);
        }
        else if (process_list[i].status == IS_TERMINATED)
        {
            printf(CYAN);
            printf(TERMINATED_s);
            printf(RESET);
        }
        

        if (process_list[i].CPUBurst < 10)
        {
            printf(" ");
        }
        if (process_list[i].CPUBurst < 100)
        {
            printf(" ");
        }

        printf("%d     ", process_list[i].CPUBurst);
    }

    printf("\n");

}

//***************************************************************************************************************************************************************//





#endif