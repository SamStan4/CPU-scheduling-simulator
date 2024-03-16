#ifndef SJF_H
#define SJF_H

#include "COMMON_scheduler_ops.h"



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

void enqueue_arriving_processes_into_ready_queue_finish_priority(_process* process_list, queue* ready_queue)
{
    int i = 0; 
    for (i = 0; i < TOTAL_CREATED_PROCESSES; ++i)
    {
        if (process_list[i].A == CURRENT_CYCLE) // enqueue the process
        {
            simulate_process_arriving_in_CPU(&process_list[i]);
            enqueue_ready_process_CPU_time_priority(ready_queue, &process_list[i]);
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

void enqueue_unblocked_processes_into_ready_queue_finish_priority(queue* ready_queue, linked_list* blocked_list)
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
            enqueue_ready_process_CPU_time_priority(ready_queue, temp);
            
        }
        else
        {
            cur_ptr = cur_ptr->nextInBlockedList;
        }
    }
}


//***************************************************************************************************************************************************************//
//     function call        : run_FCFS_routine()
//     function description : this function will run the first come first serve scheduler
//     function inputs      : _process* // list of the processes
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 2/28/2024
//     last edited          : 3/2/2024
//     programmer           : Sam Stanley

_process* performe_SJF_context_switches(_process* current_running_process, queue* ready_queue, linked_list* blocked_list)
{
    if (current_running_process == NULL)
    {
        return dequeue_ready_process(ready_queue);
    }
    else
    {
        if (is_time_to_terminate_process_Q(current_running_process) == true)
        {
            is_time_to_terminate_process_Q(current_running_process);

            simulate_terminating_a_process(current_running_process);

            return dequeue_ready_process(ready_queue);
        }
        else if (is_time_for_IO_block_Q(current_running_process) == true)
        {
            simulate_process_getting_IO_blocked(current_running_process);

            insert_blocked_list_ID_order(blocked_list, current_running_process);

            return dequeue_ready_process(ready_queue);
        }
        else
        {
            return current_running_process;
        }
    }
}

//***************************************************************************************************************************************************************//
//     function call        : run_FCFS_routine()
//     function description : this function will run the first come first serve scheduler
//     function inputs      : _process* // list of the processes
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 2/28/2024
//     last edited          : 3/2/2024
//     programmer           : Sam Stanley

void run_SJF_routine(_process* process_list, p_trace* trace)
{
    queue ready_queue;
    linked_list blocked_list;
    _process* current_running_process = NULL;

    queue_constructor(&ready_queue);
    linked_list_constructor(&blocked_list);

    sort_list_ID(process_list);

    while (TOTAL_FINISHED_PROCESSES < TOTAL_CREATED_PROCESSES)
    {
        //print_process_list_trace(process_list, TOTAL_CREATED_PROCESSES, CURRENT_CYCLE);

        push_trace(trace, process_list, TOTAL_CREATED_PROCESSES);

        enqueue_unblocked_processes_into_ready_queue_finish_priority(&ready_queue, &blocked_list);

        enqueue_arriving_processes_into_ready_queue_finish_priority(process_list, &ready_queue);

        current_running_process = performe_SJF_context_switches(current_running_process, &ready_queue, &blocked_list);

        simulate_running_a_process(current_running_process);

        blocked_list_updates(&blocked_list);

        ready_queue_updates(&ready_queue);

        CURRENT_CYCLE += 1;
    }

    sort_list_finish_time(process_list);

}

//***************************************************************************************************************************************************************//

#endif