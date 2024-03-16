#ifndef PROCESS_QUEUE_H
#define PROCESS_QUEUE_H

#include "process.h"

typedef struct queue
{
    _process* head_ptr;
    _process* tail_ptr;
    int num_processes;
} queue;

//***************************************************************************************************************************************************************//
//     function call        : queue_constructor()
//     function description : this function will initialize the contents of the queue
//     function inputs      : queue*
//     function outputs     : noneready_queue
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/2/2024
//     last edited          : 3/2/2024
//     programmer           : Sam Stanley

void queue_constructor(queue* q)
{
    q->head_ptr = NULL;
    q->tail_ptr = NULL;
    q->num_processes = 0;
}

//***************************************************************************************************************************************************************//
//     function call        : queue_destructor()
//     function description : this function will destruct the contents of the queue
//     function inputs      : queue*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/2/2024
//     last edited          : 3/2/2024
//     programmer           : Sam Stanley

void queue_destructor(queue* q)
{
    // do nothing?
    // all of the dynamic stuff will get taken care of by the process list destructor
    q->head_ptr = NULL;
    q->tail_ptr = NULL;
    q->num_processes = 0;
}

//***************************************************************************************************************************************************************//
//     function call        : is_empty()
//     function description : this function will determine if the queue is empty
//     function inputs      : queue*
//     function outputs     : bool
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/2/2024
//     last edited          : 3/2/2024
//     programmer           : Sam Stanley

bool is_empty(queue* q)
{
    if ((q->head_ptr == NULL) && (q->tail_ptr == NULL))
    {
        return true;
    }
    else
    {
        return false;
    }
}

//***************************************************************************************************************************************************************//
//     function call        : print_ready_queue_enhanced()
//     function description : this function will print the contents of the ready queue
//     function inputs      : queue
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/2/2024
//     last edited          : 3/2/2024
//     programmer           : Sam Stanley

void print_ready_queue_enhanced(queue q)
{
    _process* ptr = q.head_ptr;

    while (ptr != NULL)
    {
        print_process(ptr);
        ptr = ptr->nextInReadyQueue;
    }
}

bool search_ready_queue(queue q, _process* p)
{
    _process* cur = q.head_ptr;

    while (cur != NULL)
    {
        if (cur == p)
        {
            return true;
        }

        cur = cur->nextInReadyQueue;
    }

    return false;
}

//***************************************************************************************************************************************************************//
//     function call        : print_ready_suspended_queue_enhanced()
//     function description : this function will print the contents of the ready suspended queue
//     function inputs      : queue
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/2/2024
//     last edited          : 3/2/2024
//     programmer           : Sam Stanley

void print_ready_suspended_queue_enhanced(queue q)
{
    _process* ptr = q.head_ptr;

    while (ptr != NULL)
    {
        print_process(ptr);
        ptr = ptr->nextInReadySuspendedQueue;
    }
}

//***************************************************************************************************************************************************************//
//     function call        : enqueue_ready_process()
//     function description : this function will enqueue a process into the ready queue
//     function inputs      : queue*, _process*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/2/2024
//     last edited          : 3/2/2024
//     programmer           : Sam Stanley

void enqueue_ready_process(queue* ready_queue, _process* p)
{
    if ((p != NULL) && (ready_queue != NULL))
    {

        if (search_ready_queue(*ready_queue, p) == true)
        {
            printf("FOUND");
            pause_terminal();
        }


        p->nextInReadyQueue = NULL; // make sure this is the case

        if (ready_queue->head_ptr == NULL) // the queue is empty
        {
            ready_queue->head_ptr = p;
        }
        else // the queue is not empty
        {
            ready_queue->tail_ptr->nextInReadyQueue = p;
        }
    
        ready_queue->tail_ptr = p;

        ++ready_queue->num_processes;
    }
}

//***************************************************************************************************************************************************************//
//     function call        : enqueue_ready_suspended_process()
//     function description : this function will enqueue a process into the ready queue
//     function inputs      : queue*, _process*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/2/2024
//     last edited          : 3/2/2024
//     programmer           : Sam Stanley

void enqueue_ready_suspended_process(queue* ready_suspended_queue, _process* p)
{
    if ((p != NULL) && (ready_suspended_queue != NULL))
    {
        if (ready_suspended_queue->head_ptr == NULL) // the queue is empty
        {
            ready_suspended_queue->head_ptr = p;
        }
        else // the queue is not empty
        {
            ready_suspended_queue->tail_ptr->nextInReadySuspendedQueue = p;
        }
    
        ready_suspended_queue->tail_ptr = p;

        ++ready_suspended_queue->num_processes;
    }
}

//***************************************************************************************************************************************************************//
//     function call        : enqueue_ready_suspended_process_arrival_priority()
//     function description : this function will enqueue a process in order by its arrival time (early arrival time == high priority)
//     function inputs      : queue*, _process*
//     function outputs     : none
//     preconditions        : p is not already inside the ready suspended queue
//     postconditions       : none
//     created              ; 3/3/2024
//     last edited          : 3/3/2024
//     programmer           : Sam Stanley

// BROKEN

void enqueue_ready_suspended_process_arrival_priority(queue* ready_suspended_queue, _process* p)
{
    // _process* cur_ptr = NULL, * prev_ptr = NULL;

    // if ((ready_suspended_queue != NULL) && (p != NULL)) // just make sure
    // {
    //     cur_ptr = ready_suspended_queue->head_ptr;
    //     p->nextInReadySuspendedQueue = NULL;
    //     //p->status = 

    //     while (cur_ptr != NULL)
    //     {

    //         if (cur_ptr->A > p->A) // insert here
    //         {
    //             p->nextInReadySuspendedQueue = cur_ptr;

    //             if (prev_ptr == NULL) // insert at front
    //             {
    //                 ready_suspended_queue->head_ptr = cur_ptr;
    //             }
    //             else // inserting in the middle somewhere NOT AT THE END
    //             {
    //                 prev_ptr->nextInReadySuspendedQueue = cur_ptr;
    //             }

    //             ready_suspended_queue->num_processes++;

    //             return;
    //         }

    //         prev_ptr = cur_ptr;
    //         cur_ptr = cur_ptr->nextInReadySuspendedQueue;
    //     }

    //     if (prev_ptr == NULL) // the queue was empty
    //     {
    //         ready_suspended_queue->head_ptr = p;
    //         ready_suspended_queue->tail_ptr = p;
    //     }
    //     else // queue is not empty and we are at the end of the queue
    //     {
    //         prev_ptr->nextInReadySuspendedQueue = p;
    //         ready_suspended_queue->tail_ptr = p;
    //     }

    //     ready_suspended_queue->num_processes++;
    // }
}

//***************************************************************************************************************************************************************//
//     function call        : enqueue_ready_suspended_process_arrival_priority()
//     function description : this function will enqueue a process in order by its arrival time (early arrival time == high priority)
//     function inputs      : queue*, _process*
//     function outputs     : none
//     preconditions        : p is not already inside the ready suspended queue
//     postconditions       : none
//     created              ; 3/4/2024
//     last edited          : 3/4/2024
//     programmer           : Sam Stanley

void enqueue_ready_process_arrival_priority(queue* ready_queue, _process* p)
{
    _process* cur_ptr = NULL, * prev_ptr = NULL;

    if ((ready_queue != NULL) && (p != NULL)) // just make sure
    {
        cur_ptr = ready_queue->head_ptr;
        p->nextInReadyQueue = NULL;

        if (is_empty(ready_queue) == true)
        {
            ready_queue->head_ptr = p;
            ready_queue->tail_ptr = p;
            ready_queue->num_processes += 1;
            return;
        }
        
        while (cur_ptr != NULL)
        {
            if (cur_ptr->A > p->A) // it is time to insert [we are not at the end of the list]
            {
                p->nextInReadyQueue = cur_ptr;

                if (prev_ptr == NULL) // we are inserting at the front of the list
                {
                    ready_queue->head_ptr = p;
                }
                else // we are inserting somehere in the middle of the list
                {
                    prev_ptr->nextInReadyQueue = p;
                }

                ready_queue->num_processes += 1;

                return;
            }

            prev_ptr = cur_ptr;
            cur_ptr = cur_ptr->nextInReadyQueue;
        }


        if (prev_ptr != NULL)
        {
            prev_ptr->nextInReadyQueue = p;
            ready_queue->tail_ptr = p;
            ready_queue->num_processes += 1;
            return;
        }
        else
        {
            printf("impossible case\n");
            pause_terminal();
        }
    }
}

//***************************************************************************************************************************************************************//
//     function call        : enqueue_ready_suspended_process_arrival_priority()
//     function description : this function will enqueue a process in order by its arrival time (early arrival time == high priority)
//     function inputs      : queue*, _process*
//     function outputs     : none
//     preconditions        : p is not already inside the ready suspended queue
//     postconditions       : none
//     created              ; 3/4/2024
//     last edited          : 3/4/2024
//     programmer           : Sam Stanley

void enqueue_ready_process_CPU_time_priority(queue* ready_queue, _process* p) // mark
{
    _process* cur_ptr = NULL, * prev_ptr = NULL;

    if ((ready_queue != NULL) && (p != NULL)) // just make sure
    {
        cur_ptr = ready_queue->head_ptr;
        p->nextInReadyQueue = NULL;

        if (is_empty(ready_queue) == true)
        {
            ready_queue->head_ptr = p;
            ready_queue->tail_ptr = p;
            ready_queue->num_processes += 1;
            return;
        }
        
        while (cur_ptr != NULL)           // the second part of the condition is the tie breaker
        {
            if ((cur_ptr->C > p->C) || ((cur_ptr->C == p->C) && (cur_ptr->processID > p->processID))) // it is time to insert [we are not at the end of the list]
            {
                p->nextInReadyQueue = cur_ptr;

                if (prev_ptr == NULL) // we are inserting at the front of the list
                {
                    ready_queue->head_ptr = p;
                }
                else // we are inserting somehere in the middle of the list
                {
                    prev_ptr->nextInReadyQueue = p;
                }

                ready_queue->num_processes += 1;

                return;
            }

            prev_ptr = cur_ptr;
            cur_ptr = cur_ptr->nextInReadyQueue;
        }


        if (prev_ptr != NULL)
        {
            prev_ptr->nextInReadyQueue = p;
            ready_queue->tail_ptr = p;
            ready_queue->num_processes += 1;
            return;
        }
        else
        {
            printf("impossible case\n");
            pause_terminal();
        }
    }
}


//***************************************************************************************************************************************************************//
//     function call        : enqueue_arriving_processes_into_ready()
//     function description : this function will scan through an array and enqueue arriving processes
//     function inputs      : queue*, _process*, uint32_t
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/2/2024
//     last edited          : 3/2/2024
//     programmer           : Sam Stanley

void enqueue_arriving_processes_into_ready(queue* ready_queue, _process* process_list, int num_processes, uint32_t current_cycle)
{
    int i = 0; 
    for (i = 0; i < num_processes; ++i)
    {
        if (process_list[i].A == current_cycle) // enqueue the process
        {
            process_list[i].status = IS_READY;        // should they stay unstarted until they hit the processor?
            enqueue_ready_process(ready_queue, &process_list[i]);
        }   
    }
}

//***************************************************************************************************************************************************************//
//     function call        : dequeue_ready_process()
//     function description : this function will dequeue a ready process and return it
//     function inputs      : queue*
//     function outputs     : _process*
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/2/2024
//     last edited          : 3/2/2024
//     programmer           : Sam Stanley

_process* dequeue_ready_process(queue* ready_queue)
{
    _process* result = NULL;

    if (ready_queue != NULL)
    {
        if (is_empty(ready_queue) == false) // check if the queue is empty
        {
            result = ready_queue->head_ptr;

            if (ready_queue->head_ptr == ready_queue->tail_ptr) // there is only one element in the queue
            {
                ready_queue->head_ptr = NULL;
                ready_queue->tail_ptr = NULL;
            }
            else // there are many elements in the queue
            {
                ready_queue->head_ptr = ready_queue->head_ptr->nextInReadyQueue;
            }

            --ready_queue->num_processes;
        }
    }

    return result;
}

//***************************************************************************************************************************************************************//
//     function call        : dequeue_ready_suspended_process()
//     function description : this function will dequeue a ready suspended process and return it
//     function inputs      : queue*
//     function outputs     : _process*
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/2/2024
//     last edited          : 3/2/2024
//     programmer           : Sam Stanley

_process* dequeue_ready_suspended_process(queue* ready_suspended_queue)
{
    _process* result = NULL;

    if (ready_suspended_queue != NULL)
    {
        if (ready_suspended_queue->head_ptr != NULL) // check if the queue is empty
        {
            result = ready_suspended_queue->head_ptr;

            if (ready_suspended_queue->head_ptr == ready_suspended_queue->tail_ptr) // there is only one element in the queue
            {
                ready_suspended_queue->head_ptr = NULL;
                ready_suspended_queue->tail_ptr = NULL;
            }
            else // there are many elements in the queue
            {
                ready_suspended_queue->head_ptr = ready_suspended_queue->head_ptr->nextInReadySuspendedQueue;
            }

            --ready_suspended_queue->num_processes;
        }
    }

    return result;
}

//***************************************************************************************************************************************************************//
//     function call        : load_ready_queue()
//     function description : this function will load all of the processes into the ready queue
//     function inputs      : queue*
//     function outputs     : _process*
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/2/2024
//     last edited          : 3/2/2024
//     programmer           : Sam Stanley

void load_ready_queue(queue* ready_queue, _process* process_list)
{
    int i = 0;

    for (i = 0; i < TOTAL_CREATED_PROCESSES; ++i)
    {
        enqueue_ready_process_arrival_priority(ready_queue, &process_list[i]);
    }
}

//***************************************************************************************************************************************************************//


#endif