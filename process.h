#ifndef PROCESS_H
#define PROCESS_H

#include "RANDOM_OS.h"

#define IS_UNSTARTED 0 // same value -->
#define IS_READY 1
#define IS_RUNNING 2
#define IS_BLOCKED 3
#define IS_TERMINATED 4

#define DEFAULT_ARRIVAL_TIME 0
#define DEFAULT_CPU_BURST_UPPER_BOUND 0
#define DEFAULT_TOTAL_CPU_TIME_NEEDED 0
#define DEFAULT_CPU_TIME_MULTIPLIER 0
#define DEFAULT_PROCESS_ID 0
#define DEFAULD_STATUS 0 // <-- same value
#define DEFAULT_FINISHING_TIME -1 // invalid finishing time
#define DEFAULT_CURRENT_CPU_TIME 0
#define DEFAULT_CURRENT_IO_BLOCKED_TIME 0
#define DEFAULT_CURRENT_WAITING_TIME 0
#define DEFAULT_IO_BURST 0
#define DEFAULT_CPU_BURST 0
#define DEFAULT_QUANTUM 0
#define DEFAULT_FIRST_TIME_RUNNING true
#define DEFAULT_NEXT_IN_BLOCKED_LIST NULL
#define DEFAULT_NEXT_IN_READY_QUEUE NULL
#define DEFAULT_NEXT_IN_READY_SUSPENDED_QUEUE NULL



/* Defines a job struct */
typedef struct Process {
    uint32_t A;                         // A: Arrival time of the process
    uint32_t B;                         // B: Upper Bound of CPU burst times of the given random integer list
    uint32_t C;                         // C: Total CPU time required
    uint32_t M;                         // M: Multiplier of CPU burst time
    uint32_t processID;                 // The process ID given upon input read

    uint8_t status;                     // 0 is unstarted, 1 is ready, 2 is running, 3 is blocked, 4 is terminated

    int32_t finishingTime;              // The cycle when the the process finishes (initially -1)
    uint32_t currentCPUTimeRun;         // The amount of time the process has already run (time in running state)
    uint32_t currentIOBlockedTime;      // The amount of time the process has been IO blocked (time in blocked state)
    uint32_t currentWaitingTime;        // The amount of time spent waiting to be run (time in ready state)

    uint32_t IOBurst;                   // The amount of time until the process finishes being blocked
    uint32_t CPUBurst;                  // The CPU availability of the process (has to be > 1 to move to running)

    int32_t quantum;                    // Used for schedulers that utilise pre-emption

    bool isFirstTimeRunning;            // Used to check when to calculate the CPU burst when it hits running mode      // POTENTIAL SOURCE OF ERROR HERE!!!!!!!!!!!

    struct Process* nextInBlockedList;  // A pointer to the next process available in the blocked list
    struct Process* nextInReadyQueue;   // A pointer to the next process available in the ready queue
    struct Process* nextInReadySuspendedQueue; // A pointer to the next process available in the ready suspended queue     // for round robin only?
} _process;

//***************************************************************************************************************************************************************//
//     function call        : process_constructor()
//     function description : this function will initialize a process
//     function inputs      : _process*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/2/2024
//     last edited          : 3/2/2024
//     programmer           : Sam Stanley

void process_constructor(_process* process)
{
    //test
    //printf("inside process constructor\n");
    //end test

    process->A = DEFAULT_ARRIVAL_TIME;
    process->B = DEFAULT_CPU_BURST_UPPER_BOUND;
    process->C = DEFAULT_TOTAL_CPU_TIME_NEEDED;
    process->M = DEFAULT_CPU_TIME_MULTIPLIER;
    process->processID = DEFAULT_PROCESS_ID;
    process->status = DEFAULD_STATUS;
    process->finishingTime = DEFAULT_FINISHING_TIME;
    process->currentIOBlockedTime = DEFAULT_CURRENT_IO_BLOCKED_TIME;
    process->currentWaitingTime = DEFAULT_CURRENT_WAITING_TIME;
    process->IOBurst = DEFAULT_IO_BURST;
    process->CPUBurst = DEFAULT_CPU_BURST;
    process->quantum = DEFAULT_QUANTUM;
    process->isFirstTimeRunning = DEFAULT_FIRST_TIME_RUNNING;
    process->nextInBlockedList = DEFAULT_NEXT_IN_BLOCKED_LIST;
    process->nextInReadyQueue = DEFAULT_NEXT_IN_READY_QUEUE;
    process->nextInReadySuspendedQueue = DEFAULT_NEXT_IN_READY_SUSPENDED_QUEUE;
}

//***************************************************************************************************************************************************************//
//     function call        : populate_cpu_burst_time()
//     function description : this function will populate the CPUBurst memeber of the _process struct
//     function inputs      : _process*, int, FILE*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/2/2024
//     last edited          : 3/2/2024
//     programmer           : Sam Stanley

void print_process(_process* p)
{
    
    if (p != NULL)
    {
        printf
        (
       GREEN"Arrival time ------------------> %d\n"RESET
            "CPU burst upper bound ---------> %d\n"
            "Total CPU time needed ---------> %d\n"
            "Multiplier of CPU burst time --> %d\n"
        CYAN"Process ID --------------------> %d\n"RESET
            "Status ------------------------> %d\n"
            "Finishing time ----------------> %d\n"
            "Current CPU time run ----------> %d\n"
            "Current IO blocked time -------> %d\n"
            "Current waiting time ----------> %d\n"
            "IO burst time -----------------> %d\n"
     MAGENTA"CPU burst time ----------------> %d\n"RESET
            "Quantum -----------------------> %d\n"
            "Is first time running ---------> %d\n\n",
            p->A, p->B, p->C, p->M,
            p->processID, p->status, p->finishingTime, 
            p->currentCPUTimeRun, p->currentIOBlockedTime, 
            p->currentWaitingTime, p->IOBurst, p->CPUBurst,
            p->quantum, p->isFirstTimeRunning
        );
    }
    else
    {
        printf("PROCESS WAS NULLPTR\n");
    }
    
}

//***************************************************************************************************************************************************************//
//     function call        : populate_process_burst_time()
//     function description : this function will populate the CPUBurst memeber of the _process struct
//     function inputs      : _process*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/4/2024
//     last edited          : 3/4/2024
//     programmer           : Sam Stanley

void populate_process_CPU_burst_time(_process* prcs)
{
    uint32_t new_cpu_burst = 0;

    new_cpu_burst = random_os_wrapper(prcs->B, prcs->processID);

    prcs->CPUBurst = new_cpu_burst;
}

//***************************************************************************************************************************************************************//
//     function call        : populate_process_IO_burst_time()
//     function description : this function will populate the IOBurst memeber of the _process struct
//     function inputs      : _process*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/4/2024
//     last edited          : 3/4/2024
//     programmer           : Sam Stanley

/**
 * NOTES:
 * 
 * this is just how I think this is supposed to be done,
 * this might need to be changed, but from my understanding the IO
 * burst time is just supposed to be the CPU burst time multiplied
 * by the M data member of the _process struct
 * 
 * I could be wrong, but the requirements for this project were very unclear
 * 
*/

void populate_process_IO_burst_time(_process* prcs)
{
    uint32_t new_IO_burst = 0;

    new_IO_burst = random_os_wrapper(prcs->B, prcs->processID);

    new_IO_burst *= prcs->M;

    prcs->IOBurst = new_IO_burst;
}

//***************************************************************************************************************************************************************//
//    /$$$$$$  /$$   /$$ /$$$$$$$$  /$$$$$$  /$$$$$$$$ /$$$$$$  /$$$$$$  /$$   /$$  /$$$$$$ 
//   /$$__  $$| $$  | $$| $$_____/ /$$__  $$|__  $$__/|_  $$_/ /$$__  $$| $$$ | $$ /$$__  $$
//  | $$  \ $$| $$  | $$| $$      | $$  \__/   | $$     | $$  | $$  \ $$| $$$$| $$| $$  \__/
//  | $$  | $$| $$  | $$| $$$$$   |  $$$$$$    | $$     | $$  | $$  | $$| $$ $$ $$|  $$$$$$ 
//  | $$  | $$| $$  | $$| $$__/    \____  $$   | $$     | $$  | $$  | $$| $$  $$$$ \____  $$
//  | $$/$$ $$| $$  | $$| $$       /$$  \ $$   | $$     | $$  | $$  | $$| $$\  $$$ /$$  \ $$
//  |  $$$$$$/|  $$$$$$/| $$$$$$$$|  $$$$$$/   | $$    /$$$$$$|  $$$$$$/| $$ \  $$|  $$$$$$/
//   \____ $$$ \______/ |________/ \______/    |__/   |______/ \______/ |__/  \__/ \______/ 
//        \__/                                                                              
//***************************************************************************************************************************************************************//
//     function call        : is_quantum_expired_Q()
//     function description : this function will answer if it is time to rotate a process
//     function inputs      : _process*
//     function outputs     : bool
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/4/2024
//     last edited          : 3/4/2024
//     programmer           : Sam Stanley

bool is_quantum_expired_Q(_process* prcs)
{
    if (prcs != NULL)
    {
        if (prcs->quantum <= 0)
        {
            return true;
        }
    }

    return false;
}

//***************************************************************************************************************************************************************//
//     function call        : is_time_to_terminate_process_Q()
//     function description : this function will answer if it is time to terminate a process
//     function inputs      : _process*
//     function outputs     : bool
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/4/2024
//     last edited          : 3/4/2024
//     programmer           : Sam Stanley

bool is_time_to_terminate_process_Q(_process* prcs)
{
    if (prcs != NULL)
    {
        if (prcs->currentCPUTimeRun >= prcs->C) // if this is so, we should terminate the process
        {
            return true;
        }
    }
    
    return false;
}

//***************************************************************************************************************************************************************//
//     function call        : is_time_for_IO_block_Q()
//     function description : this function will answer if it is time to IO block a process
//     function inputs      : _process*
//     function outputs     : bool
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/4/2024
//     last edited          : 3/4/2024
//     programmer           : Sam Stanley

bool is_time_for_IO_block_Q(_process* prcs)
{
    if (prcs != NULL)
    {
        if (prcs->CPUBurst <= 0)
        {
            return true;
        }
    }

    return false;
}

//***************************************************************************************************************************************************************//
//     function call        : is_time_for_IO_block_Q()
//     function description : this function will answer if it is time to unblock a process
//     function inputs      : _process*
//     function outputs     : bool
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/4/2024
//     last edited          : 3/4/2024
//     programmer           : Sam Stanley

bool is_time_to_unblock_process_Q(_process* prcs)
{
    if (prcs != NULL)
    {
        if (prcs->IOBurst <= 0)
        {
            return true;
        }
    }

    return false;
}

//***************************************************************************************************************************************************************//
//    /$$$$$$  /$$$$$$ /$$      /$$ /$$   /$$ /$$        /$$$$$$  /$$$$$$$$ /$$$$$$  /$$$$$$$   /$$$$$$ 
//   /$$__  $$|_  $$_/| $$$    /$$$| $$  | $$| $$       /$$__  $$|__  $$__//$$__  $$| $$__  $$ /$$__  $$
//  | $$  \__/  | $$  | $$$$  /$$$$| $$  | $$| $$      | $$  \ $$   | $$  | $$  \ $$| $$  \ $$| $$  \__/
//  |  $$$$$$   | $$  | $$ $$/$$ $$| $$  | $$| $$      | $$$$$$$$   | $$  | $$  | $$| $$$$$$$/|  $$$$$$ 
//   \____  $$  | $$  | $$  $$$| $$| $$  | $$| $$      | $$__  $$   | $$  | $$  | $$| $$__  $$ \____  $$
//   /$$  \ $$  | $$  | $$\  $ | $$| $$  | $$| $$      | $$  | $$   | $$  | $$  | $$| $$  \ $$ /$$  \ $$
//  |  $$$$$$/ /$$$$$$| $$ \/  | $$|  $$$$$$/| $$$$$$$$| $$  | $$   | $$  |  $$$$$$/| $$  | $$|  $$$$$$/
//   \______/ |______/|__/     |__/ \______/ |________/|__/  |__/   |__/   \______/ |__/  |__/ \______/ 
//***************************************************************************************************************************************************************//
//     function call        : simulate_running_a_process()
//     function description : this function will simulate the process running
//     function inputs      : _process*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/4/2024
//     last edited          : 3/4/2024
//     programmer           : Sam Stanley

void simulate_running_a_process(_process* prcs)
{
    if (prcs != NULL)
    {
        prcs->status = IS_RUNNING;
        
        prcs->nextInBlockedList = NULL;    // the process shouldnt be in any of these
        prcs->nextInReadyQueue = NULL;
        prcs->nextInReadySuspendedQueue = NULL;

        if (prcs->isFirstTimeRunning == true) // if so, we need to populate the CPU burst time
        {
            populate_process_CPU_burst_time(prcs);
            prcs->isFirstTimeRunning = false;
            prcs->quantum = QUANTUM_LENGTH;
        }

        prcs->currentCPUTimeRun += 1; // most important step
        prcs->CPUBurst -= 1;
        prcs->quantum -= 1;     // for round robin
    }
    else
    {
        //TOTAL_NUMBER_OF_CYCLES_SPENT_BLOCKED += 1; // for IO util
    }
}

//***************************************************************************************************************************************************************//
//     function call        : simulate_running_a_process()
//     function description : this function will simulate the process running
//     function inputs      : _process*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/4/2024
//     last edited          : 3/4/2024
//     programmer           : Sam Stanley

void simulate_terminating_a_process(_process* prcs)
{
    if (prcs != NULL)
    {
        prcs->status = IS_TERMINATED;
        prcs->finishingTime = CURRENT_CYCLE; // also very important
        TOTAL_FINISHED_PROCESSES += 1; // most important
    }
}

//***************************************************************************************************************************************************************//
//     function call        : simulate_process_arriving_in_CPU()
//     function description : this function will simulate a process first arriving in the CPU
//     function inputs      : _process*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/4/2024
//     last edited          : 3/4/2024
//     programmer           : Sam Stanley

void simulate_process_arriving_in_CPU(_process* prcs)
{
    if (prcs != NULL)
    {
        prcs->status = IS_READY;
        prcs->isFirstTimeRunning = true;
        TOTAL_STARTED_PROCESSES += 1;
        prcs->quantum = QUANTUM_LENGTH;
    }
}

//***************************************************************************************************************************************************************//
//     function call        : simulate_unblocking_a_process()
//     function description : this function will simulate a process being unblocked, ie the process is being moved from the blocked list to the is ready queue
//     function inputs      : _process*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/4/2024
//     last edited          : 3/4/2024
//     programmer           : Sam Stanley

void simulate_unblocking_a_process(_process* prcs)
{
    if (prcs != NULL)
    {
        prcs->status = IS_READY;
        prcs->isFirstTimeRunning = true;
        prcs->nextInBlockedList = NULL;


        ////////// maybe?

        prcs->quantum = QUANTUM_LENGTH;
    }
}

//***************************************************************************************************************************************************************//
//     function call        : simulate_process_getting_IO_blocked()
//     function description : this function will simulate a process getting IO blocked
//     function inputs      : _process*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/4/2024
//     last edited          : 3/4/2024
//     programmer           : Sam Stanley

void simulate_process_getting_IO_blocked(_process* prcs)
{
    if (prcs != NULL)
    {
        prcs->status = IS_BLOCKED;
        prcs->isFirstTimeRunning = true;
        populate_process_IO_burst_time(prcs); // generate an IO burst
        prcs->nextInReadyQueue = NULL;
        prcs->quantum = QUANTUM_LENGTH;
    }
}

//***************************************************************************************************************************************************************//
//     function call        : simulate_process_waiting_in_ready_queue()
//     function description : this function will simulate a process waiting in the ready queue for one cycle
//     function inputs      : _process*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/4/2024
//     last edited          : 3/4/2024
//     programmer           : Sam Stanley

void simulate_process_waiting_in_ready_queue(_process* prcs)
{
    if (prcs != NULL)
    {
        prcs->status = IS_READY;
        prcs->currentWaitingTime += 1; // most important part
    }
}

//***************************************************************************************************************************************************************//
//     function call        : simulate_process_waiting_in_ready_queue()
//     function description : this function will simulate a process waiting in the ready queue for one cycle
//     function inputs      : _process*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/4/2024
//     last edited          : 3/4/2024
//     programmer           : Sam Stanley

void simulate_process_waiting_in_blocked_list(_process* prcs)
{
    if (prcs != NULL)
    {
        prcs->status = IS_BLOCKED;
        prcs->currentIOBlockedTime += 1; // most important part
        prcs->IOBurst -= 1; // even more important
        ++TOTAL_NUMBER_OF_CYCLES_SPENT_BLOCKED;
    }
}

//***************************************************************************************************************************************************************//
//     function call        : simulate_process_waiting_in_ready_queue()
//     function description : this function will simulate a process waiting in the ready queue for one cycle
//     function inputs      : _process*
//     function outputs     : none
//     preconditions        : none
//     postconditions       : none
//     created              ; 3/4/2024
//     last edited          : 3/4/2024
//     programmer           : Sam Stanley

void simulate_process_getting_quantum_blocked(_process* prcs)
{
    if (prcs != NULL)
    {
        prcs->quantum = QUANTUM_LENGTH;
    }
}

//***************************************************************************************************************************************************************//



#endif