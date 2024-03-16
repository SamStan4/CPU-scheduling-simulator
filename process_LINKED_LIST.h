#ifndef PROCESS_LINKED_LIST_H
#define PROCESS_LINKED_LIST_H

#include "process.h"

typedef struct linked_list
{
    _process* head_ptr;
    int num_items;
} linked_list;

//***************************************************************************************************************************************************************//
//     function call        : linked_list_constructor()
//     function description : this function will initialize the elements inside of the linked list
//     function inputs      : linked_list*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/3/2024
//     last edited          : 3/3/2024
//     programmer           : Sam Stanley

void linked_list_constructor(linked_list* list)
{
    list->head_ptr = NULL;
    list->num_items = 0;
}

//***************************************************************************************************************************************************************//
//     function call        : linked_list_destructor()
//     function description : this function will destruct the elements inside of the linked list struct
//     function inputs      : linked_list*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/3/2024
//     last edited          : 3/3/2024
//     programmer           : Sam Stanley

void linked_list_destructor(linked_list* list)
{
    // dont really need to do anything because the process list destructor will deallocate all dynamic memory
    list->head_ptr = NULL;
    list->num_items = 0;
}

//***************************************************************************************************************************************************************//
//     function call        : print_blocked_list_enhanced()
//     function description : this function will print out the contents of the linked list
//     function inputs      : linked_list*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/3/2024
//     last edited          : 3/3/2024
//     programmer           : Sam Stanley

void print_blocked_list_enhanced(linked_list list)
{
    _process* cur = list.head_ptr;

    while (cur != NULL)
    {
        print_process(cur);
        cur = cur->nextInBlockedList;
    }
}

//***************************************************************************************************************************************************************//
//     function call        : insert_front()
//     function description : this function will insert a process into the list at the front
//     function inputs      : linked_list*, _process*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/3/2024
//     last edited          : 3/3/2024
//     programmer           : Sam Stanley

void insert_blocked_list_front(linked_list* list, _process* p)
{
    if ((list != NULL) && (p != NULL))
    {
        p->nextInBlockedList = list->head_ptr;
        list->head_ptr = p;
        ++list->num_items;
    }
}

//***************************************************************************************************************************************************************//
//     function call        : insert_blocked_list_ID_order()
//     function description : this function will insert a process into the list in order by using the ID
//     function inputs      : linked_list*, _process*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/3/2024
//     last edited          : 3/3/2024
//     programmer           : Sam Stanley

void insert_blocked_list_ID_order(linked_list* list, _process* p)
{
    p->nextInBlockedList = NULL;

    _process* cur_ptr = NULL, * prev_ptr = NULL;

    if ((list != NULL) && (p != NULL))
    {
        cur_ptr = list->head_ptr;

        while (cur_ptr != NULL)
        {
            if (cur_ptr->processID > p->processID) // INSERT HERE
            {
                p->nextInBlockedList = cur_ptr;

                if (prev_ptr == NULL) // insert at front
                {
                    list->head_ptr = p;
                }
                else // not at the front
                {
                    prev_ptr->nextInBlockedList = p;
                }

                // TEST
                //printf("INSERTED\n");
                // end test

                return;
            }

            prev_ptr = cur_ptr;
            cur_ptr = cur_ptr->nextInBlockedList;
        }

        if (prev_ptr == NULL) // the list was empty
        {
            list->head_ptr = p;
        }
        else // we made it to the end of the list
        {  
            prev_ptr->nextInBlockedList = p;
        }

        list->num_items += 1;

        // TEST
        //printf("INSERTED\n");
        // end test
    }
}

//***************************************************************************************************************************************************************//
//     function call        : insert_blocked_list_ID_order()
//     function description : this function will insert a process into the list in order by using the ID
//     function inputs      : linked_list*, _process*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/3/2024
//     last edited          : 3/3/2024
//     programmer           : Sam Stanley

_process* remove_process(linked_list* list, uint32_t target_ID)
{
    _process* cur_ptr = NULL, * prev_ptr = NULL, * target_process;

    if (list != NULL)
    {
        cur_ptr = list->head_ptr;

        while (cur_ptr != NULL)
        {
            if (cur_ptr->processID == target_ID) // time to remove
            {
                target_process = cur_ptr;

                if (prev_ptr == NULL) // at the front of the list
                {
                    list->head_ptr = list->head_ptr->nextInBlockedList;
                }
                else // not at the front of the list
                {
                    prev_ptr->nextInBlockedList = cur_ptr->nextInBlockedList;
                }

                list->num_items -= 1;

                target_process->nextInBlockedList = NULL;
                return target_process;
            }

            prev_ptr = cur_ptr;
            cur_ptr = cur_ptr->nextInBlockedList;
        }
    }

    return NULL;
}

//***************************************************************************************************************************************************************//



#endif