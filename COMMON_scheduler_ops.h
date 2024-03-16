#ifndef COMMON_SCHEDULER_OPS_H
#define COMMON_SCHEDULER_OPS_H

#include "process_list.h"
#include "process_LINKED_LIST.h"
#include "process_QUEUE.h"
#include "trace.h"

//    /$$$$$$   /$$$$$$  /$$      /$$ /$$      /$$  /$$$$$$  /$$   /$$        /$$$$$$  /$$$$$$$   /$$$$$$ 
//   /$$__  $$ /$$__  $$| $$$    /$$$| $$$    /$$$ /$$__  $$| $$$ | $$       /$$__  $$| $$__  $$ /$$__  $$
//  | $$  \__/| $$  \ $$| $$$$  /$$$$| $$$$  /$$$$| $$  \ $$| $$$$| $$      | $$  \ $$| $$  \ $$| $$  \__/
//  | $$      | $$  | $$| $$ $$/$$ $$| $$ $$/$$ $$| $$  | $$| $$ $$ $$      | $$  | $$| $$$$$$$/|  $$$$$$ 
//  | $$      | $$  | $$| $$  $$$| $$| $$  $$$| $$| $$  | $$| $$  $$$$      | $$  | $$| $$____/  \____  $$
//  | $$    $$| $$  | $$| $$\  $ | $$| $$\  $ | $$| $$  | $$| $$\  $$$      | $$  | $$| $$       /$$  \ $$
//  |  $$$$$$/|  $$$$$$/| $$ \/  | $$| $$ \/  | $$|  $$$$$$/| $$ \  $$      |  $$$$$$/| $$      |  $$$$$$/
//   \______/  \______/ |__/     |__/|__/     |__/ \______/ |__/  \__/       \______/ |__/       \______/ 

//***************************************************************************************************************************************************************//
//     function call        : enqueue_arriving_processes_into_ready_queue()
//     function description : this function will enqueue arriving processes into the ready queue
//     function inputs      : _process*, queue*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/3/2024
//     last edited          : 3/3/2024
//     programmer           : Sam Stanley

void enqueue_arriving_processes_into_ready_queue(_process* process_list, queue* ready_queue)
{
    int i = 0; 
    for (i = 0; i < TOTAL_CREATED_PROCESSES; ++i)
    {
        if (process_list[i].A == CURRENT_CYCLE) // enqueue the process
        {
            simulate_process_arriving_in_CPU(&process_list[i]);
            enqueue_ready_process(ready_queue, &process_list[i]);
        }   
    }

}

//***************************************************************************************************************************************************************//
//     function call        : enqueue_unblocked_processes_into_ready_queue()
//     function description : this function will find processes to unblock and then enqueue them
//     function inputs      : queue*, linked_list*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/4/2024
//     last edited          : 3/4/2024
//     programmer           : Sam Stanley

void enqueue_unblocked_processes_into_ready_queue(queue* ready_queue, linked_list* blocked_list)
{
    _process * cur_ptr = blocked_list->head_ptr, * temp = NULL;

    while (cur_ptr != NULL)
    {
        if (is_time_to_unblock_process_Q(cur_ptr) == true) // it is time to unblock the process
        {
            temp = cur_ptr;
            cur_ptr = cur_ptr->nextInBlockedList;

            simulate_unblocking_a_process(temp);
            remove_process(blocked_list, temp->processID);
            enqueue_ready_process(ready_queue, temp);
            
        }
        else
        {
            cur_ptr = cur_ptr->nextInBlockedList;
        }
    }
}

//***************************************************************************************************************************************************************//
//     function call        : ready_queue_updates()
//     function description : this function will update the contents of the ready queue
//     function inputs      : queue*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/3/2024
//     last edited          : 3/3/2024
//     programmer           : Sam Stanley

// not validated

void ready_queue_updates(queue* read_queue)
{
    _process* cur_ptr = read_queue->head_ptr;

    while (cur_ptr != NULL)
    {
        simulate_process_waiting_in_ready_queue(cur_ptr);

        cur_ptr = cur_ptr->nextInReadyQueue;
    }
}

//***************************************************************************************************************************************************************//
//     function call        : ready_suspended_queue_updates()
//     function description : this function will update the contents of the ready queue
//     function inputs      : queue*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/3/2024
//     last edited          : 3/3/2024
//     programmer           : Sam Stanley

// not validated

void ready_suspended_queue_updates(queue* read_queue)
{
    _process* cur_ptr = read_queue->head_ptr;

    while (cur_ptr != NULL)
    {
        simulate_process_waiting_in_ready_queue(cur_ptr);

        cur_ptr = cur_ptr->nextInReadySuspendedQueue;
    }

}

//***************************************************************************************************************************************************************//
//     function call        : blocked_queue_updates()
//     function description : this function will upate the contents of the blocked queue
//     function inputs      : linked_list*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/3/2024
//     last edited          : 3/3/2024
//     programmer           : Sam Stanley

void blocked_list_updates(linked_list* blocked_list)
{
    _process* cur_ptr = blocked_list->head_ptr;

    while(cur_ptr != NULL)
    {
        simulate_process_waiting_in_blocked_list(cur_ptr);

        cur_ptr = cur_ptr->nextInBlockedList;
    }
}


//***************************************************************************************************************************************************************//


#endif