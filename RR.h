#ifndef RR_H
#define RR_H

#include "COMMON_scheduler_ops.h"

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

_process* performe_RR_context_switches(_process* current_running_process, queue* ready_queue, linked_list* blocked_list)
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
        else if (is_quantum_expired_Q(current_running_process) == true)
        {
            simulate_process_getting_quantum_blocked(current_running_process);

            enqueue_ready_process(ready_queue, current_running_process);

            return dequeue_ready_process(ready_queue);
        }
        else
        {
            return current_running_process;
        }
    }
}

//***************************************************************************************************************************************************************//
//     function call        : run_RR_routine()
//     function description : this function will run the round robin scheduler
//     function inputs      : _process* // list of the processes
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 2/28/2024
//     last edited          : 2/28/2024
//     programmer           : Sam Stanley

void run_RR_routine(_process* process_list, p_trace* trace)
{
    queue ready_queue;              // for processes that are ready to run
    linked_list blocked_list;
    _process* current_running_process = NULL;

    queue_constructor(&ready_queue);
    linked_list_constructor(&blocked_list);

    sort_list_ID(process_list);

    while (TOTAL_FINISHED_PROCESSES < TOTAL_CREATED_PROCESSES)
    {
        //print_process_list_trace(process_list, TOTAL_CREATED_PROCESSES, CURRENT_CYCLE);

        push_trace(trace, process_list, TOTAL_CREATED_PROCESSES);

        enqueue_unblocked_processes_into_ready_queue(&ready_queue, &blocked_list);

        enqueue_arriving_processes_into_ready_queue(process_list, &ready_queue);

        current_running_process = performe_RR_context_switches(current_running_process, &ready_queue, &blocked_list);

        simulate_running_a_process(current_running_process);

        blocked_list_updates(&blocked_list);

        ready_queue_updates(&ready_queue);

        ++CURRENT_CYCLE;

    }

    sort_list_finish_time(process_list);


}

//***************************************************************************************************************************************************************//


#endif